# machine_detect
 
# วิธี config ค่าในบอร์ด

## ตั้งค่าครั้งแรก
- เมื่อใช้งานครั้งแรก อุปกรณ์จะอยู่ใน AP mode(access point) หรือเป็น wifi hotspot สังเกตจะมีไฟ LED กระพริบเร็วๆ
- เชื่อมต่อเข้า ssid "icemachine" รหัสผ่าน 123456789
- เข้าหน้า http://192.168.4.1/
- และเลือก confiure page เพื่อตั้งค่าไวไฟ server ip และ sensor id
![](https://github.com/canusorn/machine_detect/blob/main/webconfig.png?raw=true)
-  บันทึกและ disconnect wifi จากบอร์ด

## ตั้งค่าผ่าน ap mode ตอนตัวบอร์ดเริ่มทำงาน 30 วินาทีแรก
- อุปกรณ์จะอยู่ใน AP mode(access point) หลังจากเริ่มทำงาน(หลังจากจ่ายไฟให้บอร์ด หรือหลังกดปุ่ม reset ที่ข้างบอร์ด) 30 วินาทีแรก สามารถเชื่อมต่อเข้า ssid "icemachine" รหัสผ่าน 123456789 และตั้งค่าได้เลย

## เข้าผ่าน ip หรือ mDNS
- เข้าผ่าน http://icemachine.local หรือ ip address ของบอร์ด (mDNS อาจไม่รองรับบนทุกอุปกรณ์ ให้เข้าผ่าน ip address ของบอร์ดแทน)

![](https://github.com/canusorn/machine_detect/blob/main/mDNS.png?raw=true)
- เลือก  configure page เพื่อเข้าหน้า config
- กรอก user: admin   password: 123456789
- จะเข้าสู่หน้าเพื่อ config ค่า

![](https://github.com/canusorn/machine_detect/blob/main/webconfig.png?raw=true)



# ไลบรารี่เพิ่มเติมสำหรับ ESP8266
- https://github.com/canusorn/IotWebConf-iotbundle
