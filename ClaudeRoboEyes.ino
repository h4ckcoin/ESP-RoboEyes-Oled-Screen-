/*
 * ClaudeRoboEyes — Retro Saat
 * ESP32 + Nokia 5110 (PCD8544) LCD — 84x48 piksel, SPI
 *
 * NOT: Bu proje PlatformIO ile derlenir (src/main.cpp).
 *      Bu .ino dosyası sadece referans amaçlıdır.
 *
 * Pin Bağlantıları:
 *   CLK  (SCK)  → GPIO 18
 *   DIN  (MOSI) → GPIO 23
 *   DC          → GPIO 2
 *   CE   (CS)   → GPIO 5
 *   RST         → GPIO 4
 *   VCC         → 3.3V  (5V VERME!)
 *   LIGHT       → GND   (arka ışık yanar)
 *   GND         → GND
 */

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define PIN_CLK   18
#define PIN_DIN   23
#define PIN_DC     2
#define PIN_CS     5
#define PIN_RST    4

Adafruit_PCD8544 display(PIN_CLK, PIN_DIN, PIN_DC, PIN_CS, PIN_RST);

const int LEFT_EYE_X  = 21;
const int RIGHT_EYE_X = 63;
const int EYE_Y       = 19;
const int EYE_A       = 14;
const int EYE_B       =  9;

const int MOUTH_CX    = 42;
const int MOUTH_Y     = 38;
const int MOUTH_A     =  8;
const int MOUTH_B_MAX =  6;

void fillEye(int cx, int openB) {
  for (int dy = -openB; dy <= openB; dy++) {
    float ratio = (float)dy / (float)EYE_B;
    float inner = 1.0f - ratio * ratio;
    int xLen = (inner > 0.0f) ? (int)(EYE_A * sqrt(inner)) : 0;
    display.drawFastHLine(cx - xLen, EYE_Y + dy, 2 * xLen + 1, BLACK);
  }
}

void drawMouth(int openB) {
  if (openB <= 0) {
    display.drawFastHLine(MOUTH_CX - MOUTH_A, MOUTH_Y, 2 * MOUTH_A + 1, BLACK);
  } else {
    for (int dy = -openB; dy <= openB; dy++) {
      float ratio = (float)dy / (float)MOUTH_B_MAX;
      float inner = 1.0f - ratio * ratio;
      int xLen = (inner > 0.0f) ? (int)(MOUTH_A * sqrt(inner)) : 0;
      display.drawFastHLine(MOUTH_CX - xLen, MOUTH_Y + dy, 2 * xLen + 1, BLACK);
    }
  }
}

void drawSmileMouth() {
  display.drawCircleHelper(MOUTH_CX, MOUTH_Y + 8, 10, 0x03, BLACK);
}

void drawFace(int eyeOpen, int mouthOpen, bool smile) {
  display.clearDisplay();
  fillEye(LEFT_EYE_X,  eyeOpen);
  fillEye(RIGHT_EYE_X, eyeOpen);
  if (smile) drawSmileMouth();
  else drawMouth(mouthOpen);
  display.display();
}

void blinkAnimation(bool smile) {
  for (int b = EYE_B; b >= 0; b -= 2) { drawFace(b, 0, smile); delay(14); }
  drawFace(0, 0, smile); delay(80);
  for (int b = 0; b <= EYE_B; b += 2) { drawFace(b, 0, smile); delay(14); }
  drawFace(EYE_B, 0, smile);
}

void smileAnimation() {
  int squintB = EYE_B * 6 / 10;
  for (int b = EYE_B; b >= squintB; b--) { drawFace(b, 0, false); delay(18); }
  drawFace(squintB, 0, true); delay(1500);
  for (int b = squintB; b <= EYE_B; b++) { drawFace(b, 0, false); delay(18); }
  drawFace(EYE_B, 0, false);
}

void talkAnimation() {
  const int pattern[] = {0, 3, 5, 6, 4, 2, 0, 3, 5, 6, 5, 2, 0,
                          2, 4, 6, 5, 2, 0, 3, 5, 4, 2, 0};
  const int patLen = sizeof(pattern) / sizeof(pattern[0]);
  for (int rep = 0; rep < 2; rep++)
    for (int i = 0; i < patLen; i++) { drawFace(EYE_B, pattern[i], false); delay(75); }
  drawFace(EYE_B, 0, false);
}

void setup() {
  display.begin();
  display.setBias(4);
  display.setContrast(60);
  display.clearDisplay();
  display.display();
}

void loop() {
  drawFace(EYE_B, 0, false);
  delay(2000);
  blinkAnimation(false);
  delay(1000);
  talkAnimation();
  delay(1000);
  blinkAnimation(false);
  delay(1000);
  smileAnimation();
  delay(500);
}
