
  --------- <img width="381" height="701" alt="Ekran Resmi 2026-03-18 23 02 33" src="https://github.com/user-attachments/assets/8e33447e-fb51-4ec7-8b26-ec082d0e17e2" /> ------
   

# ClaudeRoboEyes — OLED

ESP32 ve SSD1306 OLED ekranı kullanarak yumuşak animasyonlu robot gözleri. Gözler otomatik göz kırpar, farklı yönlere bakar ve mutlu, yorgun, kafası karışık gibi ifadeler sergiler. [FluxGarage RoboEyes](https://github.com/FluxGarage/RoboEyes) kütüphanesi üzerine kurulmuştur.

---

## Ne Yapar?

- Yumuşak animasyonlu iki robot gözü gösterir (128x64 SSD1306 OLED ekranında)
- Her 3 saniyede bir otomatik göz kırpar
- Her 4 saniyede bir gözler rastgele yön değiştirir (sağ, sol, yukarı, aşağı)
- Her 6 saniyede bir yüz ifadesi döngüsel olarak değişir:
  - **Normal** — sakin, nötr bakış
  - **Mutlu** — neşeli göz şekli
  - **Gülme** — gözler yukarı-aşağı titrer
  - **Yorgun** — gözkapakları yarı kapalı
  - **Kafası karışık** — gözler sağa-sola titrer
- Merak modu: sağa/sola bakınca dış göz büyür

---

## Gerekli Donanım

| Parça | Adet |
|---|---|
| ESP32 Dev Board | 1 |
| SSD1306 OLED 128x64 (5 pinli, I2C) | 1 |
| Jumper kablo | 5 adet |
| Breadboard | 1 (isteğe bağlı) |

---

## Bağlantı Şeması

OLED modülünün üzerindeki pin isimlerine bakarak bağla:

| OLED Pin | ESP32 Pin | Açıklama |
|---|---|---|
| GND | GND | Toprak |
| VCC | **3.3V** | Güç |
| SCL | GPIO 22 | I2C saat sinyali |
| SDA | GPIO 21 | I2C veri |
| RES | GPIO 16 | Ekran sıfırlama |

> **Uyarı:** VCC için **3.3V** kullan. 5V bağlarsan ekran zarar görebilir.

---

## Yazılım Kurulumu

### 1. Gereksinimler

- [VSCode](https://code.visualstudio.com/) veya [Cursor](https://www.cursor.com/)
- [PlatformIO IDE eklentisi](https://platformio.org/install/ide?install=vscode)

### 2. Projeyi Klonla

```bash
git clone https://github.com/h4ckcoin/ClaudeRoboEyes_OLED.git
cd ClaudeRoboEyes_OLED
```

### 3. Kütüphaneleri Yükle ve Derle

PlatformIO kütüphaneleri otomatik indirir. Terminal açıp şunu çalıştır:

```bash
pio run
```

### 4. ESP32'ye Yükle

ESP32'yi USB ile bilgisayara bağla, ardından:

```bash
pio run --target upload
```

Veya PlatformIO arayüzünde **"Upload"** butonuna tıkla.

---

## I2C Adresi Ayarı

Çoğu SSD1306 modülü `0x3C` adresini kullanır. Ekran görünmüyorsa `0x3D` deneyebilirsin:

```cpp
#define SCREEN_ADDRESS 0x3C  // Görünmüyorsa 0x3D yap
```

---

## Göz Boyutunu Özelleştirme

`src/main.cpp` içinde bu değerleri değiştirerek gözlerin görünümünü ayarlayabilirsin:

```cpp
eyes.setWidth(38, 38);        // sol göz genişliği, sağ göz genişliği (piksel)
eyes.setHeight(28, 28);       // sol göz yüksekliği, sağ göz yüksekliği (piksel)
eyes.setBorderradius(8, 8);   // köşe yuvarlama (0 = kare, yüksek = daire)
eyes.setSpacebetween(16);     // iki göz arasındaki boşluk (piksel)
```

---

## Animasyon Hızını Ayarlama

İfade döngüsü hızını değiştirmek için `loop()` içindeki değeri düzenle:

```cpp
if (millis() - lastMood > 6000) {  // 6000ms = 6 saniye
```

---

## Proje Yapısı

```
ClaudeRoboEyes_OLED/
├── src/
│   └── main.cpp          — Ana kaynak kod
├── platformio.ini         — PlatformIO konfigürasyonu ve kütüphaneler
├── ClaudeRoboEyes.ino     — Arduino IDE referans dosyası
└── README.md              — Bu dosya
```

---

## Kullanılan Kütüphaneler

| Kütüphane | Sürüm | Açıklama |
|---|---|---|
| [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) | ^2.5.9 | SSD1306 OLED sürücüsü |
| [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) | ^1.11.9 | Grafik temel kütüphanesi |
| [FluxGarage RoboEyes](https://github.com/FluxGarage/RoboEyes) | latest | Robot gözü animasyon motoru |

---

## Lisans

MIT License — özgürce kullanabilir, değiştirebilir ve paylaşabilirsin.
