#include "PicoGo.h"

PicoGo::PicoGo(){
}

bool PicoGo::begin(){

  pinMode(PIN_IR_DETECTOR_R, INPUT);
  pinMode(PIN_IR_DETECTOR_L, INPUT);
  pinMode(PIN_ULTRASONIC_TRG, OUTPUT);
  pinMode(PIN_ULTRASONIC_ECHO, INPUT);

  canvas = new LGFX_Sprite(&lcd);
  // ディスプレイの初期設定
  lcd.init();
  // 画面右で折り返す設定
  canvas->setTextWrap(true);
  // 画面サイズでキャンバス用のメモリを確保
  canvas->createSprite(lcd.width(), lcd.height());
  // 黒で塗りつぶし
  canvas->fillScreen(TFT_BLACK);
  // 文字色は白
  canvas->setTextColor(TFT_WHITE);
  // デフォルトカーソル位置
  canvas->setCursor(0, 0);
  // デフォルトフォント
  canvas->setFont(&fonts::lgfxJapanMincho_20);

  return true;
}

LGFX_Sprite* PicoGo::getCanvas(){
  return canvas;
}

bool PicoGo::getIrDetectorRight(){
  return (bool)!digitalRead(PIN_IR_DETECTOR_R);
}

bool PicoGo::getIrDetectorLeft(){
  return (bool)!digitalRead(PIN_IR_DETECTOR_L);
}

int PicoGo::getUltrasonicDistance(){
  digitalWrite(PIN_ULTRASONIC_TRG, LOW);    // set trig pin low 2μs
  delayMicroseconds(2);
  digitalWrite(PIN_ULTRASONIC_TRG, HIGH);   // set trig pin 10μs , at last 10us 
  delayMicroseconds(10);
  digitalWrite(PIN_ULTRASONIC_TRG, LOW);    // set trig pin low
  float Fdistance = pulseIn(PIN_ULTRASONIC_ECHO, HIGH);  // Read echo pin high level time(us)
  Fdistance= Fdistance/58;                  //Y m=（X s*344）/2
                                            // X s=（ 2*Y m）/344 ==》X s=0.0058*Y m ==》cm = us /58       
  return (int)Fdistance;
}  