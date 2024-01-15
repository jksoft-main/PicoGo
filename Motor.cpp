#include "Motor.h"

#define AIN1_PIN  18
#define AIN2_PIN  17
#define PWMA_PIN  16
#define BIN1_PIN  19
#define BIN2_PIN  20
#define PWMB_PIN  21

Motor::Motor(){

}

void Motor::begin(){
  pinMode(AIN1_PIN, OUTPUT);
  pinMode(AIN2_PIN, OUTPUT);
  pinMode(BIN1_PIN, OUTPUT);
  pinMode(BIN2_PIN, OUTPUT);
}

void Motor::control(int right,int left){
  if(right >= 0){
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, HIGH);
    right = right > 255 ? 255 : right;
    analogWrite(PWMB_PIN,right);
  } else {
    digitalWrite(BIN1_PIN, HIGH);
    digitalWrite(BIN2_PIN, LOW);
    right = -right > 255 ? 255 : -right;
    analogWrite(PWMB_PIN,right);
  }
  if(left >= 0){
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, HIGH);
    left = left > 255 ? 255 : left;
    analogWrite(PWMA_PIN,left);
  } else {
    digitalWrite(AIN1_PIN, HIGH);
    digitalWrite(AIN2_PIN, LOW);
    left = -left > 255 ? 255 : -left;
    analogWrite(PWMA_PIN,left);
  }
}

void Motor::stop(){
  digitalWrite(AIN1_PIN, HIGH);
  digitalWrite(AIN2_PIN, HIGH);
  digitalWrite(BIN1_PIN, HIGH);
  digitalWrite(BIN2_PIN, HIGH);
}