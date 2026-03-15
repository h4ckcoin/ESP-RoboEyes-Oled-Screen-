/*
 * ClaudeRoboEyes — FluxGarage RoboEyes
 * ESP32 + SSD1306 OLED (I2C) — 128x64 piksel
 *
 * Pin Bağlantıları:
 *   VCC  → 3.3V
 *   GND  → GND
 *   SCL  → GPIO 22
 *   SDA  → GPIO 21
 *   RES  → GPIO 16
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ESP32 Arduino.h ile RoboEyes DEFAULT makro çakışmasını önle
#ifdef DEFAULT
  #undef DEFAULT
#endif
#include <FluxGarage_RoboEyes.h>

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT   64
#define OLED_RESET      16
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RoboEyes<Adafruit_SSD1306> eyes(display);

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for (;;);  // Ekran bulunamazsa dur
  }
  display.clearDisplay();
  display.display();

  // RoboEyes başlat — 128x64, max 60fps
  eyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 60);

  // 128x64 için göz boyutları:
  // 2×38px + 16px ara = 92px → her iki yanda 18px boşluk
  // Göz yüksekliği: 28px → üst/alt 18px boşluk
  eyes.setWidth(38, 38);
  eyes.setHeight(28, 28);
  eyes.setBorderradius(8, 8);
  eyes.setSpacebetween(16);

  // Monochrome OLED: arka plan=0 (siyah), çizim=1 (beyaz)
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
      case 0: eyes.setMood(DEFAULT);                       break;  // Normal
      case 1: eyes.setMood(HAPPY);                         break;  // Mutlu
      case 2: eyes.anim_laugh();  eyes.setMood(HAPPY);     break;  // Gülen
      case 3: eyes.setMood(TIRED);                         break;  // Yorgun
      case 4: eyes.anim_confused(); eyes.setMood(DEFAULT); break;  // Şaşırmış
    }
    moodIndex++;
  }

  eyes.update();
}
