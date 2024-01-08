// PicoGo ラインセンサー確認用スケッチ
#include "PicoGo.h"
#include "TRSensors.h"
#include "Wire.h"

PicoGo picoGo;
TRSensors trs;
unsigned int sensorValues[5];

void setup() {
  trs.begin();
  picoGo.begin();
}

void loop() {
  LGFX_Sprite* cv = picoGo.getCanvas();
  trs.AnalogRead(sensorValues);
  cv->fillScreen(TFT_BLACK);
  cv->setCursor(0, 0);
  cv->printf("ラインセンサーの状態\n");
  cv->printf("%d\n",sensorValues[0]);
  cv->printf("%d\n",sensorValues[1]);
  cv->printf("%d\n",sensorValues[2]);
  cv->printf("%d\n",sensorValues[3]);
  cv->printf("%d\n",sensorValues[4]);
  cv->pushSprite(0, 0);
  delay(100);
}
