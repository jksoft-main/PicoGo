// PicoGo 赤外線対物センサー確認用スケッチ
#include "PicoGo.h"

PicoGo picoGo;

void setup() {
  picoGo.begin();
}

void loop() {
  LGFX_Sprite* cv = picoGo.getCanvas();
  cv->fillScreen(TFT_BLACK);
  cv->setCursor(0, 0);
  cv->printf("赤外線対物センサーの状態\n");
  if(picoGo.getIrDetectorLeft()){
    cv->printf("●");
  } else {
    cv->printf("◯");
  }
  if(picoGo.getIrDetectorRight()){
    cv->printf("●");
  } else {
    cv->printf("◯");
  }
  cv->pushSprite(0, 0);
  delay(100);
}
