#include "PicoGo.h"


#define KP  100    // 比例ゲイン

const int target = 5;   // 目標値

PicoGo picoGo;
bool start_flag = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  picoGo.begin();

  // 停止する
  picoGo.stop();
  // スピードを小さくする
  picoGo.setMaxSpeed(100);

}

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
    int sensor = picoGo.getUltrasonicDistance();
    // 誤差を求める
    int err = target - sensor;
    // P制御で、制御入力を求める
    int u = KP * err;
    // モーターを制御する

    if( u < 0) {
      picoGo.setSpeed(-u);
      picoGo.forward();
    } else {
      picoGo.setSpeed(u);
      picoGo.backward();
    }
  }
}