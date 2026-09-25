# SmartMailBox

ESP8266 (NodeMCU) ควบคุมรีเลย์ล็อก/ปลดล็อกตู้จดหมายผ่าน Firebase Realtime Database และแจ้งสถานะ WiFi ผ่าน LINE Notify

## Hardware
- ESP8266 (NodeMCU / Wemos D1 mini)
- Relay module ต่อที่ขา `D0`

## Libraries (ติดตั้งผ่าน Library Manager)
- Firebase ESP8266 Client (`FirebaseESP8266`)
- TridentTD_LineNotify
- DHT sensor library

Board: ESP8266 (เพิ่ม Board Manager URL `http://arduino.esp8266.com/stable/package_esp8266com_index.json`)

## Setup หลัง clone
1. คัดลอก `secrets.example.h` เป็น `secrets.h`
   ```
   copy secrets.example.h secrets.h
   ```
2. แก้ค่าใน `secrets.h` (WiFi, LINE token, Firebase host/auth)
3. เปิด `SmartMailBox.ino` ด้วย Arduino IDE (หรือ VS Code + Arduino extension) เลือกบอร์ด แล้ว Upload

> `secrets.h` ถูกใส่ไว้ใน `.gitignore` จะไม่ถูกอัปโหลดขึ้น GitHub

## Firebase
- `/Mail/StatusLock/status` : `"LOCK"` หรือ `"UNLOCK"` (อ่านเพื่อสั่งรีเลย์)
- `/Mail/StatusWifi` : สถานะ WiFi (เขียนโดยบอร์ด)
