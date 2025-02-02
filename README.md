# 🌡️ ESP32 IoT Sıcaklık ve LED Kontrol Sistemi

<div align="center">

![GitHub last commit](https://img.shields.io/github/last-commit/brkyozclkl/Control-LEDs-and-monitor-temperature-humidity-via-web-server-on-ESP32)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![ESP32](https://img.shields.io/badge/ESP32-v4.4+-blue.svg)](https://www.espressif.com/)
[![DHT11](https://img.shields.io/badge/Sensor-DHT11-green.svg)](https://www.adafruit.com/product/386)

<h3>🚀 Web Tabanlı IoT Sıcaklık, Nem İzleme ve LED Kontrol Sistemi</h3>

[Özellikler](#özellikler) •
[Donanım](#donanım-gereksinimleri) •
[Kurulum](#kurulum) •
[Devre Şeması](#devre-şeması) •
[Kod](#kod-açıklaması)

<img src="docs/project-preview.jpg" alt="Project Preview" width="600"/>

</div>

## ✨ Özellikler

<div align="center">

| 🎯 Özellik | 📝 Açıklama |
|------------|-------------|
| 🌡️ **Sıcaklık ve Nem İzleme** | DHT11 sensörü ile gerçek zamanlı ölçüm |
| 💡 **3x LED Kontrolü** | Web arayüzü üzerinden 3 ayrı LED kontrolü |
| 🔄 **Otomatik Yenileme** | 4 saniyelik aralıklarla veri güncelleme |
| 📱 **Responsive Tasarım** | Mobil uyumlu web arayüzü |
| 📊 **Görsel Göstergeler** | Font Awesome ikonları ile zengin görsel arayüz |
| 📡 **WiFi Bağlantısı** | Kablosuz erişim ve kontrol imkanı |

</div>

## 🛠️ Donanım Gereksinimleri

- ESP32 Geliştirme Kartı
- DHT11 Sıcaklık ve Nem Sensörü
- 3x LED
- 3x 220Ω Direnç
- Breadboard
- Jumper Kablolar

## 📝 Kurulum

1. **Arduino IDE Kurulumu ve Ayarları**
   - Arduino IDE'yi yükleyin
   - ESP32 board desteği için yönetici URL'sini ekleyin:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```

2. **Gerekli Kütüphaneler**
   - WiFi.h
   - WebServer.h
   - DHT.h

3. **WiFi Yapılandırması**
```cpp
const char* ssid = "WiFi_Adınız";
const char* password = "WiFi_Şifreniz";
```

## 🔌 Pin Bağlantıları

```
ESP32     DHT11    LED1    LED2    LED3
3.3V  -->  VCC
GIO27  -->  DATA
GND   -->  GND
GIO32  ----[220Ω]---->|    
GIO33  ----[220Ω]----------->|
GIO26  ----[220Ω]---------------->|
```

## 💻 Kod Açıklaması

### Ana Bileşenler
1. **WiFi Bağlantısı**: ESP32'nin WiFi ağına bağlanması
2. **Web Server**: HTTP isteklerini işleyen asenkron web sunucusu
3. **DHT11 Sensör**: Sıcaklık ve nem verilerinin okunması
4. **LED Kontrolü**: 3 ayrı LED'in web arayüzü üzerinden kontrolü

### Önemli Fonksiyonlar
```cpp
void handleRoot() {
    // Web sayfası HTML içeriğinin oluşturulması
}

float readDHTTemperature() {
    // Sıcaklık verisinin okunması
}

float readDHTHumidity() {
    // Nem verisinin okunması
}
```

### Web Arayüzü
- Sıcaklık ve nem değerlerinin görüntülenmesi
- Her LED için açma/kapama butonları
- 4 saniyelik otomatik sayfa yenileme
- Responsive tasarım

## 📱 Arayüz Görüntüsü

<div align="center">
<img src="docs/interface.jpg" width="300" />
</div>

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
