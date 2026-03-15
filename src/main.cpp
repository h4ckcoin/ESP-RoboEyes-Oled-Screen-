/*
 * ClaudeRoboEyes — FluxGarage RoboEyes
 * ESP32 + Nokia 5110 (PCD8544) LCD — 84x48 piksel, SPI
 *
 * Pin Bağlantıları:
 *   CLK  (SCK)  → GPIO 18
 *   DIN  (MOSI) → GPIO 23
 *   DC          → GPIO 2
 *   CE   (CS)   → GPIO 5
 *   RST         → GPIO 4
 *   VCC         → 5V  (bu modül 5V istiyor!)
 *   LIGHT       → GND (arka ışık yanar)
 *   GND         → GND
 */

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// ESP32 Arduino.h ile RoboEyes DEFAULT makro çakışmasını önle
#ifdef DEFAULT
  #undef DEFAULT
#endif
#include <FluxGarage_RoboEyes.h>

#define PIN_DC   2
#define PIN_CS   5
#define PIN_RST  4

Adafruit_PCD8544 display(PIN_DC, PIN_CS, PIN_RST);
RoboEyes<Adafruit_PCD8544> eyes(display);

void setup() {
  // RST manuel sıfırlama — bazı modüller bunu gerektirir
  pinMode(PIN_RST, OUTPUT);
  digitalWrite(PIN_RST, LOW);
  delay(100);
  digitalWrite(PIN_RST, HIGH);
  delay(100);

  // Nokia 5110 başlatma
  display.begin();
  display.setBias(7);
  display.setContrast(60);
  display.clearDisplay();
  display.display();

  // RoboEyes başlat — 84x48, max 30fps (Nokia 5110 yavaş)
  eyes.begin(84, 48, 30);

  // Nokia 5110 = 84x48 piksel
  // Göz boyutu: 2×30px + 10px ara = 70px → her iki yanda 7px boşluk
  // Göz yüksekliği: 22px → üst/alt 13px boşluk
  eyes.setWidth(30, 30);
  eyes.setHeight(22, 22);
  eyes.setBorderradius(6, 6);
  eyes.setSpacebetween(10);

  // Monochrome LCD: arka plan=0, çizim=1
  eyes.setDisplayColors(0, 1);

  // Otomatik göz kırpma: her 3±2 sn
  eyes.setAutoblinker(ON, 3, 2);

  // Boşta rastgele bakış: her 4±2 sn
  eyes.setIdleMode(ON, 4, 2);

  // Merak modu: sağa/sola bakarken dış göz büyür
  eyes.setCuriosity(ON);
}

unsigned long lastMood = 0;
int moodIndex = 0;

void loop() {
  // Her 6 saniyede bir ifade değiştir
  if (millis() - lastMood > 6000) {
    lastMood = millis();
    switch (moodIndex % 5) {
      case 0: eyes.setMood(DEFAULT);                     break;
      case 1: eyes.setMood(HAPPY);                       break;
      case 2: eyes.anim_laugh();  eyes.setMood(HAPPY);   break;
      case 3: eyes.setMood(TIRED);                       break;
      case 4: eyes.anim_confused(); eyes.setMood(DEFAULT); break;
    }
    moodIndex++;
  }

  eyes.update();
}
