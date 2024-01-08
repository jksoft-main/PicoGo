// PicoGo ディスプレイ表示確認用スケッチ
#include "PicoGo.h"

PicoGo picoGo;

void setup() {
  picoGo.begin();
}

void loop() {
  static int count = 0;

  LGFX_Sprite* cv = picoGo.getCanvas();
  cv->fillScreen(TFT_BLACK);
  cv->setCursor(0, 0);
  cv->printf("数値をカウントします\n");
  cv->printf("%d",count++);
  cv->pushSprite(0, 0);
  delay(1000);
}
