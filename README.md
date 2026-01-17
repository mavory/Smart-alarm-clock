# Smart Alarm Clock (SAC)

Using ESP32 you can have your own alarm clock that is controllable via the web!

## Why did I do this?

I was always late or needed some encouragement! So I created SAC, which is web-controlled and very compact and minimalist. Now I can adjust my alarm clock via the web on my PC while I'm in the kitchen (for example).

## Features

- Web interface
- You can edit alarms via the web
- You see diagnostics on the display
- Day/night mode

## Scripts

It's the only script you need and it's about 460 lines long! It contains everything from libraries to the website. 
Just edit the WiFi and password on line 237 and you can upload it straight to the ESP32 and everything should work.

### Home page:
![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6ODE0ODQsInB1ciI6ImJsb2JfaWQifX0=--8e1259e238cdfaa1b2f501dad1e71752abc713b6/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)

## How it works?

On the website you choose what you need, for example, you create a one-day alarm clock with vibration and buzzer for 21:30. At 21:30 your alarm will start and you can turn it off using the button on the website or via the button directly on the alarm clock.
Also, if you press the button twice, you will see all current alarms on the display and if you hold the button, you will get to the diagnostics, where you can see all important information!

### Libraries:

```
- Arduino.h
- WiFi.h
- ESPAsyncWebServer.h 
- AsyncTCP.h
- Adafruit_NeoPixel.h
- LittleFS.h
- SD.h
- SPI.h
- Wire.h
- Adafruit_GFX.h
- Adafruit_SSD1306.h
- RtcDS1302.h
- ThreeWire.h
- OneButton.h
- time.h
```

## 3D models

Here is a view of the top and bottom of the case:

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6ODM5NDgsInB1ciI6ImJsb2JfaWQifX0=--06ebcd7e911fc4bc47ec1ec3d452ae756a5d462b/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6ODM5NTAsInB1ciI6ImJsb2JfaWQifX0=--fc1622a893fa68390f869b42fc7bcdb0e2b7ce32/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)

## Wiring Diagram

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6ODQ0MjIsInB1ciI6ImJsb2JfaWQifX0=--ffbffc0ae510820d4a9844dc0a7807686647b4d9/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/Sn%C3%ADmek%20obrazovky%202026-01-17%20152935.png)

## There is the final video of how it works!!

_Here is a youtube video where you can see how it works:_ [Link](https://youtu.be/AV3PfRDRrco)

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6ODQwMzMsInB1ciI6ImJsb2JfaWQifX0=--c98bf6a66e933c4757320215c66313a7b9d9eea8/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/20260116_232608.jpg)
