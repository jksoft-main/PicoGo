#include "PicoGo.h"

PicoGo picoGo;

void setup() {
  picoGo.begin();
  // 停止する
  picoGo.stop();
  // スピードを小さくする
  picoGo.setSpeed(50);

}

void loop() {
  unsigned char results;

  if(picoGo.IR_decode(&results)) {
    if(results != 0x09) return;
    // １．壁に近づく
    // 右モーターを前進
    picoGo.forward();
    // １秒待つ
    delay(1000);
    // 停止
    picoGo.stop();
  }
}