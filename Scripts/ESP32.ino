#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RtcDS1302.h>
#include <ThreeWire.h>
#include <OneButton.h>
#include "time.h"

//PINOUT
#define PIN_SD_CS    5
#define PIN_BUZZER   33
#define PIN_VIBRO    26   //zde je ten pin pro motor
#define PIN_BTN      4
#define PIN_LDR      34
#define OLED_SDA     21
#define OLED_SCL     22

ThreeWire myWire(14, 13, 27); // DAT, CLK, RST!!!!!
RtcDS1302<ThreeWire> Rtc(myWire);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
AsyncWebServer server(80);
OneButton button(PIN_BTN, true);

bool isAlarmActive = false;
bool oledPower = true;
String globalIP = "0.0.0.0";
unsigned long lastUpdate = 0;
unsigned long stateTimer = 0;
unsigned long bootTime = 0;

enum State { CLOCK, LIST, DIAG };
State displayState = CLOCK;

// Alarm settingues
int actBuzzer = 1;
int actVibro = 1;
int actFreq = 1500;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;     //pro mě to ej gmt+1
const int   daylightOffset_sec = 3600; // letní čas

// esp32 čip teplota
#ifdef __cplusplus
extern "C" { uint8_t temprature_sens_read(); }
#endif

// logika tlacitka
void handleClick() {
  if (isAlarmActive) {
    // stop alarmu
    isAlarmActive = false;
    noTone(PIN_BUZZER);
    digitalWrite(PIN_VIBRO, LOW);
  } else {
    if (!oledPower) {
      oledPower = true;
    } else {
      displayState = CLOCK;
    }
  }
}

void handleDoubleClick() {
  if(!isAlarmActive) { displayState = LIST; stateTimer = millis(); }
}

void handleLongPress() {
  if(!isAlarmActive) { displayState = DIAG; stateTimer = millis(); }
}

void runVibrationEffect() {
  unsigned long m = millis();
  if (actVibro == 1) { 
    // konstanta
    digitalWrite(PIN_VIBRO, HIGH); 
  } 
  else if (actVibro == 2) { 
    int p = m % 1000;
    if ((p > 0 && p < 150) || (p > 250 && p < 400)) digitalWrite(PIN_VIBRO, HIGH);
    else digitalWrite(PIN_VIBRO, LOW);
  }
}

// web, jako vzdy hrozne
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>VORY OS V5</title>
<style>
  :root { --bg: #ffffff; --text: #000000; --acc: #000000; }
  body { background: var(--bg); color: var(--text); font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif; margin: 0; padding: 20px; max-width: 600px; margin: auto; }
  h1 { border-bottom: 4px solid var(--text); padding-bottom: 10px; letter-spacing: -1px; text-transform: uppercase; }
  .card { border: 2px solid #eee; padding: 20px; border-radius: 12px; margin-bottom: 20px; box-shadow: 0 4px 10px rgba(0,0,0,0.05); }
  label { font-size: 10px; font-weight: 800; text-transform: uppercase; color: #888; display: block; margin-bottom: 8px; }
  .grid { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; }
  input, select, button { width: 100%; box-sizing: border-box; padding: 12px; border: 2px solid #ddd; border-radius: 8px; font-size: 14px; font-weight: 600; background: #fff; appearance: none; }
  input:focus, select:focus { border-color: #000; outline: none; }
  button { background: #000; color: #fff; border-color: #000; cursor: pointer; transition: 0.2s; }
  button:hover { background: #333; transform: translateY(-2px); }
  button.danger { background: #ff3b30; border-color: #ff3b30; }
  button.danger:hover { background: #d63026; }
  .alarm-item { display: flex; justify-content: space-between; align-items: center; padding: 15px 0; border-bottom: 1px solid #eee; }
  .tag { font-size: 10px; background: #eee; padding: 4px 8px; border-radius: 4px; margin-left: 5px; }
  #status-dot { height: 10px; width: 10px; background-color: #ccc; border-radius: 50%; display: inline-block; margin-right: 5px; }
  .online { background-color: #34c759 !important; }
</style>
<script>
  function el(id){ return document.getElementById(id); }
  function toggleDate(v){ el('date_box').style.display = (v==='once') ? 'block' : 'none'; }
  
  function loadData() {
    fetch('/api/list').then(r=>r.text()).then(h => el('alarm-list').innerHTML = h);
    fetch('/api/status').then(r=>r.json()).then(j => {
      el('sys-status').innerText = j.status;
      el('sys-temp').innerText = j.temp + "°C";
      el('sd-usage').innerText = j.sd;
      el('status-dot').className = (j.online ? 'online' : '');
    });
  }
  
  function sendCmd(cmd) { fetch('/cmd?do='+cmd).then(()=>loadData()); }
  
  function addAlarm() {
    let t = el('t').value, m = el('m').value;
    let d = (m === 'daily') ? 'daily' : el('d_val').value;
    let b = el('b').value, v = el('v').value, f = el('f').value;
    if(!t) return alert("Please set time!");
    
    fetch(`/api/add?t=${t}&d=${d}&b=${b}&v=${v}&f=${f}`).then(() => {
      el('t').value = '';
      loadData();
    });
  }
  
  function delAlarm(id) {
    if(confirm("Delete this alarm?")) {
      fetch(`/api/del?id=${id}`).then(()=>loadData());
    }
  }

  setInterval(loadData, 2000);
</script>
</head>
<body onload="loadData()">
  <h1>VORY OS <span style="font-size:12px; vertical-align:middle; background:#000; color:#fff; padding:2px 6px; border-radius:4px;">PRO</span></h1>
  
  <div class="card">
    <div style="display:flex; justify-content:space-between;">
      <div><span id="status-dot"></span><span id="sys-status">LOADING...</span></div>
      <div id="sys-temp">--°C</div>
    </div>
    <div style="margin-top:10px; font-size:12px; color:#666;">SD Storage: <span id="sd-usage">--</span></div>
  </div>

  <div class="card">
    <label>Control Center</label>
    <div class="grid">
      <button onclick="sendCmd('oled')">Toggle OLED</button>
      <button onclick="sendCmd('ntp')">NTP Sync (Net)</button>
      <button onclick="sendCmd('test_vib')">Test Motor</button>
      <button class="danger" onclick="sendCmd('kill')">STOP ALARM</button>
    </div>
  </div>

  <div class="card">
    <label>New Alarm</label>
    <div class="grid">
      <input type="time" id="t">
      <select id="m" onchange="toggleDate(this.value)">
        <option value="daily">Repeat Daily</option>
        <option value="once">One-time (Date)</option>
      </select>
    </div>
    <div id="date_box" style="display:none; margin-bottom:10px;">
      <input type="date" id="d_val">
    </div>
    <div class="grid">
      <select id="b"><option value="1">Buzzer: Loud</option><option value="2">Buzzer: Pulse</option><option value="0">Silent</option></select>
      <select id="v"><option value="1">Vibro: Constant</option><option value="2">Vibro: Heartbeat</option><option value="0">Off</option></select>
    </div>
    <input type="number" id="f" value="1500" placeholder="Hz (Pitch)">
    <button onclick="addAlarm()" style="margin-top:10px;">SAVE ALARM</button>
  </div>

  <div class="card">
    <label>Active Alarms</label>
    <div id="alarm-list">Loading...</div>
  </div>
</body>
</html>
)rawliteral";

// seťup
void setup() {
  Serial.begin(115200);
  bootTime = millis();
  
  pinMode(PIN_VIBRO, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LDR, INPUT);
  
  // test motoru
  digitalWrite(PIN_VIBRO, HIGH); delay(200); digitalWrite(PIN_VIBRO, LOW);

  Wire.begin(OLED_SDA, OLED_SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  // booting animacia
  display.clearDisplay();
  display.setTextSize(1); display.setTextColor(WHITE);
  display.setCursor(30, 20); display.println("VORY OS V5");
  display.drawRect(14, 40, 100, 10, WHITE);
  for(int i=0; i<100; i+=10) {
    display.fillRect(16, 42, i, 6, WHITE);
    display.display();
    delay(50);
  }

  button.setClickTicks(200);
  button.setPressTicks(2000);
  button.attachClick(handleClick);
  button.attachDoubleClick(handleDoubleClick);
  button.attachLongPressStart(handleLongPress);

  Rtc.Begin();
  if (!SD.begin(PIN_SD_CS)) { Serial.println("SD Fail"); }

  // WiFi
  WiFi.begin("Vory", "Pazout2604"); // CHANGE PASSWORD
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 10) { delay(500); attempt++; }
  if(WiFi.status() == WL_CONNECTED) globalIP = WiFi.localIP().toString();
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *r){ r->send(200, "text/html", index_html); });
  
  server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest *r){
    String json = "{";
    json += "\"status\":\"" + String(isAlarmActive ? "ALARM ACTIVE" : "SYSTEM READY") + "\",";
    json += "\"temp\":\"" + String((temprature_sens_read() - 32) / 1.8, 1) + "\",";
    json += "\"online\":" + String(WiFi.status() == WL_CONNECTED ? "true" : "false") + ",";
    json += "\"sd\":\"" + String(SD.totalBytes() / (1024*1024)) + " MB\"";
    json += "}";
    r->send(200, "application/json", json);
  });

  server.on("/cmd", HTTP_GET, [](AsyncWebServerRequest *r){
    String cmd = r->getParam("do")->value();
    if(cmd == "oled") oledPower = !oledPower;
    else if(cmd == "kill") { isAlarmActive = false; noTone(PIN_BUZZER); digitalWrite(PIN_VIBRO, LOW); }
    else if(cmd == "test_vib") { 
      digitalWrite(PIN_VIBRO, HIGH); delay(1000); digitalWrite(PIN_VIBRO, LOW); 
    }
    else if(cmd == "ntp") {
      struct tm timeinfo;
      if(getLocalTime(&timeinfo)){
        RtcDateTime now(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        Rtc.SetDateTime(now);
      }
    }
    r->send(200);
  });

  server.on("/api/list", HTTP_GET, [](AsyncWebServerRequest *r){
    File f = SD.open("/alarms.txt", FILE_READ);
    String html = ""; int id = 0;
    if(!f){ r->send(200, "text/plain", "SD Error"); return; }
    
    while(f.available()){
      String l = f.readStringUntil('\n');
      if(l.length() > 5) {
        int s1 = l.indexOf('|'); int s2 = l.indexOf('|', s1+1);
        String t = l.substring(0, s1); 
        String d = l.substring(s1+1, s2);
        if(d != "daily") { 
            // Format 2026-01-12 -> 12.01.
            d = d.substring(8,10) + "." + d.substring(5,7) + "."; 
        } else {
            d = "Daily";
        }
        
        html += "<div class='alarm-item'>";
        html += "<div><span style='font-size:18px; font-weight:bold'>" + t + "</span> <span class='tag'>" + d + "</span></div>";
        html += "<button class='danger' style='width:auto; padding:5px 10px; font-size:12px' onclick='delAlarm("+String(id)+")'>DEL</button>";
        html += "</div>";
        id++;
      }
    }
    f.close();
    r->send(200, "text/html", html.length() > 0 ? html : "No Alarms Set");
  });

  server.on("/api/add", HTTP_GET, [](AsyncWebServerRequest *r){
    String row = r->getParam("t")->value() + "|" + r->getParam("d")->value() + "|" + r->getParam("b")->value() + "|" + r->getParam("v")->value() + "|" + r->getParam("f")->value();
    File f = SD.open("/alarms.txt", FILE_APPEND); f.println(row); f.close();
    r->send(200);
  });

  server.on("/api/del", HTTP_GET, [](AsyncWebServerRequest *r){
    int id = r->getParam("id")->value().toInt();
    File f = SD.open("/alarms.txt", FILE_READ);
    String content = ""; int cnt = 0;
    while(f.available()){
      String l = f.readStringUntil('\n');
      if(cnt != id && l.length() > 0) content += l + "\n";
      cnt++;
    }
    f.close();
    SD.remove("/alarms.txt"); // Clean delete
    File fw = SD.open("/alarms.txt", FILE_WRITE);
    fw.print(content);
    fw.close();
    r->send(200);
  });

  server.begin();
}

// loopppp
void loop() {
  button.tick();
  
  if(displayState != CLOCK && millis() - stateTimer > 10000) displayState = CLOCK;

  RtcDateTime now = Rtc.GetDateTime();

  if (now.Second() == 0 && !isAlarmActive) {
    File f = SD.open("/alarms.txt", FILE_READ);
    char curT[6], curD[11];
    sprintf(curT, "%02d:%02d", now.Hour(), now.Minute());
    sprintf(curD, "%04d-%02d-%02d", now.Year(), now.Month(), now.Day());
    
    while(f.available()){
      String l = f.readStringUntil('\n');
      if (l.startsWith(curT)) {
        int s1 = l.indexOf('|'); int s2 = l.indexOf('|', s1+1);
        int s3 = l.indexOf('|', s2+1); int s4 = l.indexOf('|', s3+1);
        
        String d = l.substring(s1+1, s2);
        if (d == "daily" || d == String(curD)) {
          isAlarmActive = true;
          actBuzzer = l.substring(s2+1, s3).toInt();
          actVibro = l.substring(s3+1, s4).toInt();
          actFreq = l.substring(s4+1).toInt();
          break; // trigger
        }
      }
    }
    f.close();
  }

  if (isAlarmActive) {
    unsigned long m = millis();
    
    if (actBuzzer == 1) tone(PIN_BUZZER, actFreq);
    else if (actBuzzer == 2) tone(PIN_BUZZER, (m % 500 < 250) ? actFreq : 0);
    else noTone(PIN_BUZZER);

    runVibrationEffect();
  }

  // oled
  if (millis() - lastUpdate > 200) {
    lastUpdate = millis();
    display.clearDisplay();

    if (!oledPower && !isAlarmActive) {
      display.display(); // OFF
    } 
    else {
      int ldr = analogRead(PIN_LDR);
      bool isNight = (ldr < 800);
      display.ssd1306_command(SSD1306_SETCONTRAST);
      display.ssd1306_command(isNight ? 0x01 : 0xCF); // snížení jasu

      if (isAlarmActive) {
        // ALARM 
        static bool flash = false; flash = !flash;
        if(flash) display.fillRect(0,0,128,64, WHITE);
        display.setTextColor(flash ? BLACK : WHITE);
        display.setTextSize(3); 
        display.setCursor(20, 22); display.print("ALARM");
      } 
      else {
        display.setTextColor(WHITE);
        
        if (displayState == CLOCK) {
          // datum
          display.setTextSize(1);
          char dBuf[20]; 
          sprintf(dBuf, "%02d/%02d/%04d", now.Day(), now.Month(), now.Year());
          display.setCursor(0, 0); display.print(dBuf);
          
          if(WiFi.status() == WL_CONNECTED) {
            display.setCursor(100,0); display.print("WiFi");
          }

          // separator
          display.drawFastHLine(0, 10, 128, WHITE);

          // body
          display.setTextSize(4);
          char tBuf[6]; sprintf(tBuf, "%02d:%02d", now.Hour(), now.Minute());
          
          // velky text
          display.setCursor(5, 18); 
          display.print(tBuf);

          // separator
          display.drawFastHLine(0, 52, 128, WHITE);

          // footer
          display.setTextSize(1);
          display.setCursor(0, 56);
          display.print(isNight ? "MODE: NIGHT" : "MODE: DAY");
        } 
        else if (displayState == LIST) {
          display.setTextSize(1); 
          display.setCursor(0,0); display.println("ALARM LIST");
          display.drawFastHLine(0, 9, 128, WHITE);
          
          File f = SD.open("/alarms.txt", FILE_READ);
          int rowY = 12;
          int count = 0;
          while(f.available() && count < 4) {
            String l = f.readStringUntil('\n');
            int pipe = l.indexOf('|');
            if(pipe > 0) {
              String t = l.substring(0, pipe);
              display.setCursor(0, rowY);
              display.print("> " + t);
              rowY += 10;
              count++;
            }
          }
          f.close();
          if(count==0) { display.setCursor(0,12); display.print("No Alarms"); }
        }
        else if (displayState == DIAG) {
          display.setTextSize(1);
          display.setCursor(0,0); display.println("SYSTEM INFO");
          display.drawFastHLine(0, 9, 128, WHITE);
          display.setCursor(0,12);
          display.print("IP: "); display.println(globalIP);
          display.print("RAM: "); display.print(ESP.getFreeHeap()/1024); display.println(" KB");
          display.print("UP: "); display.print(millis()/60000); display.println(" min");
          display.print("VIB: "); display.println(actVibro);
        }
      }
      display.display();
    }
  }
}