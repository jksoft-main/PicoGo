#include "Adafruit_NeoPixel.h"
#include "PicoGo.h"

#define LED_PIN     22

// NeoPixelのインスタンス
Adafruit_NeoPixel RGB = Adafruit_NeoPixel(4, LED_PIN, NEO_GRB + NEO_KHZ800);
// PicoGoのインスタンス
PicoGo picoGo;

bool start_flag = false;

void setup() {
  // NeoPixelの初期化
  RGB.begin();
  // PicoGoの初期化
  picoGo.begin();
  // 停止する
  picoGo.stop();
  // スピードを小さくする
  picoGo.setMaxSpeed(50);
}

// スケッチを変更して、壁にぶつからない様にロボットを動かして下さい

// モーターコントロール方法
// 前進：picoGo.forward();
// 後退：picoGo.backward();
// 右旋回：picoGo.right();
// 左旋回：picoGo.left();

void loop() {
  unsigned char results;

  if(picoGo.IR_decode(&results)) {
    if(results == 0x09){
      digitalWrite(LED_BUILTIN, HIGH);
      start_flag = true;
    } else if(results == 0x1c){
      digitalWrite(LED_BUILTIN, LOW);
      start_flag = false;
      picoGo.stop();
    }
  }
  if(start_flag) {
    // 前進
    picoGo.forward();

    // 赤外線対物センサーが反応したらNeoPixelを点灯
    if(picoGo.getIrDetectorRight()){
      RGB.setPixelColor(0, 0xFF0000);
      RGB.setPixelColor(1, 0xFF0000);
    } else {
      RGB.setPixelColor(0, 0x000000);
      RGB.setPixelColor(1, 0x000000);
    }
    if(picoGo.getIrDetectorLeft()){
      RGB.setPixelColor(2, 0xFF0000);
      RGB.setPixelColor(3, 0xFF0000);
    } else {
      RGB.setPixelColor(2, 0x000000);
      RGB.setPixelColor(3, 0x000000);
    }
    RGB.show();
  }
}
