#include "PicoGo.h"

PicoGo picoGo;

// 左モーター
#define AIN1_PIN  18
#define AIN2_PIN  17
#define PWMA_PIN  16
// 右モーター
#define BIN1_PIN  19 
#define BIN2_PIN  20
#define PWMB_PIN  21

void setup() {
  picoGo.begin();
  // ピンの初期設定
  pinMode(AIN1_PIN, OUTPUT);
  pinMode(AIN2_PIN, OUTPUT);
  pinMode(PWMA_PIN, OUTPUT);
  pinMode(BIN1_PIN, OUTPUT);
  pinMode(BIN2_PIN, OUTPUT);
  pinMode(PWMB_PIN, OUTPUT);
  digitalWrite(PWMA_PIN, HIGH);
  digitalWrite(PWMB_PIN, HIGH);
  // analogWrite(PWMA_PIN,50);
  // analogWrite(PWMB_PIN,50);
}

void loop() {
  unsigned char results;

  if(picoGo.IR_decode(&results))
  {
    if(results != 0x09) return;
    // １．右モーターを1秒間正転し、停止する
    // 右モーターを正転
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, HIGH);
    // １秒待つ
    delay(1000);
    // 右モーターを停止
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, LOW);

    // ２．左モーターを2秒間逆転し、停止する
    // 左モーターを正転
    digitalWrite(AIN1_PIN, HIGH);
    digitalWrite(AIN2_PIN, LOW);
    // ２秒待つ
    delay(2000);
    // 左モーターを停止
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, LOW);

    // ３．3秒間待つ
    delay(3000);

    // ４．右モーターと左モーターを3秒間正転し、停止する
    // 右モーターを正転
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, HIGH);
    // 左モーターを正転
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, HIGH);
    // ３秒待つ
    delay(3000);
    // 右モーターを停止
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, LOW);
    // 左モーターを停止
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, LOW);
  }
}