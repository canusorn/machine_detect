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
- หลังบันทึกแล้ว แนะนำให้รีเซตบอร์ดใหม่ เพื่อให้ค่าอัพเดทเป็นค่าล่าสุด

# อัดโหลดหรืออัพเดทโค้ด
## การอัพโหลดไฟล์ bin ผ่าน nodemcu-flasher
- https://iotkiddie.com/blog/docs/binary-flasher/
## การอัพเดทเฟิมแวร์ออนไลน์ด้วยไฟล์ bin
- ไฟล์ bin จะอยู่ในโฟลเดอร์เดียวกับโค้ด
- เข้าหน้า configure ด้วยวิธีด้านบน
- ด้านล่างของ form จะมีตัวเลือก อัพเดทเฟิร์มแวร์
- อัพโหลดไฟล์ binary(.bin) ในตัวเลือก firmware บอร์ดจะทำการอัพเดทให้เอง
![](https://github.com/canusorn/machine_detect/blob/main/firmware.png?raw=true)

##  การอัพโหลดโค้ดเองผ่าน Arduino IDE
- https://medium.com/@pechpijitthapudom/%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B8%95%E0%B8%B4%E0%B8%94%E0%B8%95%E0%B8%B1%E0%B9%89%E0%B8%87-esp8266-arduino-core-%E0%B9%80%E0%B8%9E%E0%B8%B7%E0%B9%88%E0%B8%AD%E0%B9%83%E0%B8%8A%E0%B9%89%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%81%E0%B8%B1%E0%B8%9A-arduino-ide-7ad468e969e6
- ติดตั้งไลบรารี่เพิ่มเติม https://github.com/canusorn/IotWebConf-iotbundle
- เปิดไฟล์ espMachineDetect.ino เลือกบอร์ดและพอร์ตให้ถูกต้อง (ในที่นี้เลือก Wemos d1 mini) และอัพโหลด

#  PHP
- ติดตั้ง xampp https://fastclick.co.th/howto-install-xampp-windows/
- Run XAMPP at Windows Startup http://pmcom.blogspot.com/2014/09/run-xampp-at-windows-startup-xampp.html
- เปลี่ยนพอร์ต https://medium.com/@codingthailand/%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B9%80%E0%B8%9B%E0%B8%A5%E0%B8%B5%E0%B9%88%E0%B8%A2%E0%B8%99-port-mysql-%E0%B8%88%E0%B8%B2%E0%B8%81-3306-%E0%B9%80%E0%B8%9B%E0%B9%87%E0%B8%99-port-%E0%B8%AD%E0%B8%B7%E0%B9%88%E0%B8%99-xampp-7091f4dddc88
- ในไฟล์ในโฟลเดอร์ php ไปวางไว้ใน C:\xampp\htdocs
- ตั้งค่า username และ mysql database ที่ไฟล์ includes.php ที่ฟังก์ชั่น getconn ของคลาส Database

# ไฟล์
- espMachineDetect โค้ดสำหรับบอร์ด esp8266
- php โค้ด php สำหรับติดตั้งบนคอมพิวเตอร์
