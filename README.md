# 🌡️ ESP32 IoT Temperature & LED Control System

<div align="center">

<h3>🚀 Web Tabanlı IoT Sıcaklık İzleme ve LED Kontrol Sistemi</h3>


<img src="docs/project-preview.jpg" alt="Project Preview" width="600"/>

</div>

## ✨ Özellikler

<div align="center">

| 🎯 Özellik | 📝 Açıklama |
|------------|-------------|
| 🌡️ **Sıcaklık İzleme** | Gerçek zamanlı sıcaklık ve nem takibi |
| 💡 **LED Kontrolü** | Web arayüzü üzerinden LED kontrolü |
| 📊 **Grafik Arayüz** | Sıcaklık ve nem verilerinin grafiksel gösterimi |
| 📱 **Responsive Tasarım** | Mobil uyumlu web arayüzü |
| 🔄 **Otomatik Yenileme** | Anlık veri güncelleme |
| 📡 **WiFi Bağlantısı** | Kablosuz erişim ve kontrol |

</div>

## 🛠️ Donanım Gereksinimleri

- ESP32 Geliştirme Kartı
- DHT11/DHT22 Sıcaklık ve Nem Sensörü
- LED'ler (x3)
- 220Ω Dirençler (x3)
- Breadboard
- Jumper Kablolar

## 📝 Kurulum

1. **Arduino IDE Kurulumu**
```bash
# ESP32 board URL'sini Arduino IDE'ye ekleyin
https://dl.espressif.com/dl/package_esp32_index.json
```

2. **Gerekli Kütüphaneler**
- ESPAsyncWebServer
- AsyncTCP
- DHT sensor library
- Adafruit Unified Sensor

3. **WiFi Yapılandırması**
```cpp
const char* ssid = "WiFi_Adınız";
const char* password = "WiFi_Şifreniz";
```

## 📊 Web Arayüzü Özellikleri

- **Gerçek Zamanlı Veriler**
  - Anlık sıcaklık gösterimi
  - Nem seviyesi takibi
  - LED durumları

- **Kontrol Paneli**
  - LED açma/kapama düğmeleri
  - Veri güncelleme hızı ayarı
  - Sistem durumu göstergesi

## 🔌 Devre Şeması

```
ESP32     DHT11/22    LED1    LED2    LED3
3.3V  -->  VCC
GIO21  -->  DATA
GND   -->  GND
GIO19  ---------------[220Ω]---->|
GIO18  ---------------[220Ω]---->|
GIO5   ---------------[220Ω]---->|
```

## 🚀 Nasıl Çalışır?

1. ESP32, DHT sensöründen sıcaklık ve nem verilerini okur
2. Async Web Server üzerinden web arayüzü sunulur
3. JavaScript ile veriler düzenli olarak güncellenir
4. WebSocket bağlantısı ile LED kontrolü sağlanır



## 👨‍💻 Geliştirici

<div align="center">
  
**Berkay Özçelikel**

[![Mail](https://img.shields.io/badge/Mail-D14836?logo=gmail&logoColor=white)](mailto:berkayozcelikel0@gmail.com)

</div>



---

<div align="center">
⭐️ Bu projeyi beğendiyseniz yıldız vermeyi unutmayın!

<i>Bu proje IoT ve ev otomasyonu öğrenme amacıyla geliştirilmiştir.</i>
</div>
