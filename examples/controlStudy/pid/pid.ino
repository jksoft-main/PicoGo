#include "PicoGo.h"


#define KP  20    // 比例ゲイン
#define KI  0.5   // 積分ゲイン
#define KD  0.5   // 微分ゲイン

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
    if(results == 0x09) {
      digitalWrite(LED_BUILTIN, HIGH);
      start_flag = true;
    } else if(results == 0x1c) {
      digitalWrite(LED_BUILTIN, LOW);
      start_flag = false;
      picoGo.stop();
    }
  }

  if(start_flag) {
    static int prev_err = 0;
    static float pre_time = micros();
    static float i = 0;

    int sensor = picoGo.getUltrasonicDistance();
    // 誤差を求める
    int err = target - sensor;
    // 差分時間を求める
    float dt = (micros() - pre_time) / 1000000;
    pre_time = micros();
    // 積分値を求める
    i += err * dt;
    // 微分値を求める
    float d = (err - prev_err) / dt;
    prev_err = err;
    // PID制御器で制御入力を求める
    int u = KP * err + KI * i + KD * d;

    if( u < 0) {
      picoGo.setSpeed(-u);
      picoGo.forward();
    } else {
      picoGo.setSpeed(u);
      picoGo.backward();
    }
  }
}