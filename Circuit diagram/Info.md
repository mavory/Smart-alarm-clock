# Wiring Diagram 


### Inputs:
- **Button:**
  - SIG: GPIO 4
  - VCC: 5V 
  - GND: GND
- **LDR Photosensor:**
  - SIG: GPIO 34
  - Circuit: 3.3V --- LDR --- GPIO 34 --- 10k resistor --- GND

### Outputs:
- **Vibration Motor Module:**
  - SIG: GPIO 26
  - VCC: 5V
  - GND: GND
- **Buzzer Module:**
  - SIG: GPIO 33
  - GND: GND

### Display & Storage:
- **OLED Display:**
  - SDA: GPIO 21
  - SCL: GPIO 22
  - VCC: 5V
  - GND: GND
- **MicroSD Card Module (SPI):**
  - CS: GPIO 5
  - MOSI: GPIO 23
  - MISO: GPIO 19
  - SCK: GPIO 18
  - VCC: 5V
  - GND: GND

### Real Time Clock:
- **RTC DS1302 (3-Wire):**
  - DAT (I/O): GPIO 14
  - CLK (SCLK): GPIO 13
  - RST (CE): GPIO 27
  - VCC: 3.3V
  - GND: GND
