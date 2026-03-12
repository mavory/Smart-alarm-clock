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

https://www.tinkercad.com/things/f3PBRpHUPhY-clock?sharecode=p_ixkk5DhO9dDXulNEwirXyC8I3PMVLbobYcKOfEwlo

Here is a view of the top and bottom of the case:

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6ODM5NDgsInB1ciI6ImJsb2JfaWQifX0=--06ebcd7e911fc4bc47ec1ec3d452ae756a5d462b/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6ODM5NTAsInB1ciI6ImJsb2JfaWQifX0=--fc1622a893fa68390f869b42fc7bcdb0e2b7ce32/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)

## Wiring Diagram

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6ODQ0MjIsInB1ciI6ImJsb2JfaWQifX0=--ffbffc0ae510820d4a9844dc0a7807686647b4d9/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/Sn%C3%ADmek%20obrazovky%202026-01-17%20152935.png)

## BOM (Bill of Materials)

| Item | Quantity | Price | Link |
|------|----------|-------|------|
| ESP32 | 1 | $5.43 | [Buy](https://www.aliexpress.com/item/1005009694232832.html?spm=a2g0o.productlist.main.1.5b8bc3f5B8HmYK&aem_p4p_detail=2026010206593715418004120532860003007959&algo_pvid=0f6d7b6e-c833-4946-b692-b332ab2295a3&algo_exp_id=0f6d7b6e-c833-4946-b692-b332ab2295a3-0&pdp_ext_f=%7B%22order%22%3A%22841%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21CZK%21116.69%21116.69%21%21%215.55%215.55%21%402103867617673659779095273ecb8a%2112000049877962179%21sea%21CZ%213289986290%21X%211%210%21n_tag%3A-29919%3Bd%3A7b8fc234%3Bm03_new_user%3A-29895&curPageLogUid=bPYYmnweQOZ8&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005009694232832%7C_p_origin_prod%3A&search_p4p_id=2026010206593715418004120532860003007959_1) |
| OLED display | 1 | $1.44 | [Buy](https://www.aliexpress.com/item/32896971385.html?spm=a2g0o.order_list.order_list_main.73.59371802jT2w75) |
| SD card module | 1 | $0.56 | [Buy](https://www.aliexpress.com/item/1005009113598175.html?spm=a2g0o.order_list.order_list_main.48.59371802jT2w75) |
| Breadboard | 1 | $2.56 | [Buy](https://www.aliexpress.com/item/1005009799908389.html) |
| Vibration motor | 1 | $0.8 | [Buy](https://www.aliexpress.com/item/1005005518779084.html?spm=a2g0o.order_list.order_list_main.84.59371802jT2w75) |
| Buzzer | 1 | $1.28 | [Buy](https://www.aliexpress.com/item/1005006260328559.html?spm=a2g0o.productlist.main.1.453422aaKms6QJ&aem_p4p_detail=20260102065614197141902846080003241083&algo_pvid=1067701f-d8a4-4073-b522-5bab83d10f92&algo_exp_id=1067701f-d8a4-4073-b522-5bab83d10f92-0&pdp_ext_f=%7B%22order%22%3A%22319%22%2C%22spu_best_type%22%3A%22order%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21CZK%2127.75%2124.39%21%21%211.32%211.16%21%402103847817673657740211243ef0d6%2112000036509108003%21sea%21CZ%213289986290%21X%211%210%21n_tag%3A-29919%3Bd%3A7b8fc234%3Bm03_new_user%3A-29895&curPageLogUid=u9zf8d5xh8uM&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006260328559%7C_p_origin_prod%3A&search_p4p_id=20260102065614197141902846080003241083_1) |
| Jumpers | Much | $4.73 | [Buy](https://www.aliexpress.com/item/1005002611994443.html?spm=a2g0o.productlist.main.28.7dc96f23Txzygz&algo_pvid=f0be8999-2c3a-4069-80dc-26b5da2359cc&algo_exp_id=f0be8999-2c3a-4069-80dc-26b5da2359cc-27&pdp_ext_f=%7B%22order%22%3A%2213%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21CZK%2147.63%2147.63%21%21%212.24%212.24%21%4021038e6617651173371191604ebe80%2112000021387001543%21sea%21CZ%213289986290%21X%211%210%21n_tag%3A-29912%3Bd%3A7b8fc234%3Bm03_new_user%3A-29895&curPageLogUid=fx2zB0EGcu5H&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005002611994443%7C_p_origin_prod%3A) |
| Button | 1 | $.2.02 | [Buy](https://www.aliexpress.com/item/1005007197228321.html?spm=a2g0o.productlist.main.39.89a15f75EL5YJ8&algo_pvid=861677b9-9cad-4bce-95e7-1d46c515099f&algo_exp_id=861677b9-9cad-4bce-95e7-1d46c515099f-38&pdp_ext_f=%7B%22order%22%3A%2213%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21CZK%2155.68%2144.54%21%21%212.60%212.08%21%402103835e17685934825381313e1b63%2112000039769859949%21sea%21CZ%213289986290%21X%211%210%21n_tag%3A-29919%3Bd%3A7b8fc234%3Bm03_new_user%3A-29895&curPageLogUid=niWf4yREvIVl&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005007197228321%7C_p_origin_prod%3A) |
| RTC modul | 1 | $1.78 | [Buy](https://www.aliexpress.com/item/1005006627321251.html?spm=a2g0o.productlist.main.13.28b34fd99WdIOj&algo_pvid=f66d8425-dd6d-43aa-8716-71319ca883a5&algo_exp_id=f66d8425-dd6d-43aa-8716-71319ca883a5-12&pdp_ext_f=%7B%22order%22%3A%2257%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21CZK%21118.57%2137.95%21%21%2138.56%2112.34%21%4021038e1e17685935383182820eebeb%2112000037942428152%21sea%21CZ%213289986290%21X%211%210%21n_tag%3A-29919%3Bd%3A7b8fc234%3Bm03_new_user%3A-29895&curPageLogUid=19tjyUq9NzO2&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006627321251%7C_p_origin_prod%3A) |
| Shipping to CZ | / | $3.96 | / |

## There is the final video of how it works!!

_Here is a youtube video where you can see how it works:_ [Link](https://youtu.be/AV3PfRDRrco)

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6ODQwMzMsInB1ciI6ImJsb2JfaWQifX0=--c98bf6a66e933c4757320215c66313a7b9d9eea8/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/20260116_232608.jpg)
