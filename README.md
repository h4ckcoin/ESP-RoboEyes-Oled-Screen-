# ClaudeRoboEyes

ESP32 ve Nokia 5110 LCD ekranı kullanarak yumuşak animasyonlu robot gözleri. Gözler otomatik göz kırpar, farklı yönlere bakar ve mutlu, yorgun, sinirli gibi ifadeler sergiler. [FluxGarage RoboEyes](https://github.com/FluxGarage/RoboEyes) kütüphanesi üzerine kurulmuştur.

---

## Ne Yapar?

- Yumuşak animasyonlu iki robot gözü gösterir (Nokia 5110'un nostaljik yeşil/mavi LCD ekranında)
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
| Nokia 5110 LCD (PCD8544, kırmızı kart) | 1 |
| Jumper kablo | 8 adet |
| Breadboard | 1 (isteğe bağlı) |

---

## Bağlantı Şeması

Nokia 5110 modülünün üzerindeki pin isimlerine bakarak bağla:

| Nokia 5110 Pin | ESP32 Pin | Açıklama |
|---|---|---|
| RST | GPIO 4 | Ekran sıfırlama |
| CE (CS) | GPIO 5 | Chip seçimi |
| DC | GPIO 2 | Veri / Komut seçimi |
| DIN (MOSI) | GPIO 23 | Veri girişi |
| CLK (SCK) | GPIO 18 | SPI saat sinyali |
| VCC | **5V** | Güç — bu modül 5V istiyor! |
| LIGHT | GND | Arka ışık (GND'ye bağlayınca yanar) |
| GND | GND | Toprak |

> **Uyarı:** VCC için ESP32'nin **5V (VIN)** pinini kullan. 3.3V bağlarsan ekranda hiçbir şey görünmez.

---

## Yazılım Kurulumu

### 1. Gereksinimler

- [VSCode](https://code.visualstudio.com/) veya [Cursor](https://www.cursor.com/)
- [PlatformIO IDE eklentisi](https://platformio.org/install/ide?install=vscode)

### 2. Projeyi Klonla

```bash
git clone https://github.com/KULLANICI_ADIN/ClaudeRoboEyes.git
cd ClaudeRoboEyes
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

## Kontrast Ayarı

Bazı Nokia 5110 modülleri farklı kontrast değerlerine ihtiyaç duyar. Ekran çok koyu veya çok soluk görünüyorsa `src/main.cpp` dosyasındaki şu satırı değiştir:

```cpp
display.setContrast(60);  // 40 ile 80 arasında dene
```

---

## Göz Boyutunu Özelleştirme

`src/main.cpp` içinde bu değerleri değiştirerek gözlerin görünümünü ayarlayabilirsin:

```cpp
eyes.setWidth(30, 30);        // sol göz genişliği, sağ göz genişliği (piksel)
eyes.setHeight(22, 22);       // sol göz yüksekliği, sağ göz yüksekliği (piksel)
eyes.setBorderradius(6, 6);   // köşe yuvarlama (0 = kare, yüksek = daire)
eyes.setSpacebetween(10);     // iki göz arasındaki boşluk (piksel)
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
ClaudeRoboEyes/
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
| [Adafruit PCD8544](https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library) | ^2.0.1 | Nokia 5110 LCD sürücüsü |
| [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) | ^1.11.9 | Grafik temel kütüphanesi |
| [FluxGarage RoboEyes](https://github.com/FluxGarage/RoboEyes) | latest | Robot gözü animasyon motoru |

---

## Lisans

MIT License — özgürce kullanabilir, değiştirebilir ve paylaşabilirsin.
