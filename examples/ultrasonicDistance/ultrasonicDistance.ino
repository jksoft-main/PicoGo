// PicoGo 超音波距離センサー確認用スケッチ
#include "PicoGo.h"

PicoGo picoGo;

void setup() {
  picoGo.begin();
}

void loop() {
  LGFX_Sprite* cv = picoGo.getCanvas();
  cv->fillScreen(TFT_BLACK);
  cv->setCursor(0, 0);
  cv->printf("超音波距離センサーの状態\n");
  cv->printf("%d",picoGo.getUltrasonicDistance());
  cv->pushSprite(0, 0);
  delay(100);
}
