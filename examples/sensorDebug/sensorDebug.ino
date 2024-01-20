#include "Adafruit_NeoPixel.h"
#include "PicoGo.h"
#include "TRSensors.h"

#define LED_PIN     22
#define BUZZER_PIN  4

// NeoPixelのインスタンス
Adafruit_NeoPixel RGB = Adafruit_NeoPixel(4, LED_PIN, NEO_GRB + NEO_KHZ800);
// PicoGoのインスタンス
PicoGo picoGo;
// ラインセンサーのインスタンス
TRSensors trs;

unsigned int sensorValues[5];
struct repeating_timer st_timer;

bool Timer(struct repeating_timer *t){
  // 超音波距離センサーが5cm以下だったらブザーを鳴らす
  if( picoGo.getUltrasonicDistance() <= 5){
    // ブザーを鳴らす
    digitalWrite(BUZZER_PIN,HIGH);
  } else {
    // ブザーを止める
    digitalWrite(BUZZER_PIN,LOW);
  }
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

  // ラインセンサーの値をLCDに表示
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

  return true;
}

void setup() {
  // ブザー用のピンを初期化
  pinMode(BUZZER_PIN,OUTPUT);
  // NeoPixelの初期化
  RGB.begin();
  // PicoGoの初期化
  picoGo.begin();
  // ラインセンサーの初期化
  trs.begin();
  // 500msのタイマーでセンサーを監視
  add_repeating_timer_us(500000, Timer, NULL, &st_timer);
}

void loop() {
  // リモコンにしたがってモーターをコントロール
  static unsigned long lasttime = 0;
  unsigned char results;
  int speed = picoGo.getSpeed();

  if(picoGo.IR_decode(&results))
  {
    switch(results){
      case 0x18:
        picoGo.forward();
        break;
      case 0x52:
        picoGo.backward();
        break;
      case 0x5A:
        picoGo.right();
        break;
      case 0x08:
        picoGo.left();
        break;
      case 0x1c:
        picoGo.stop();
        break;
      case 0x15:
        speed += 10;
        speed = speed > 255 ? 255 : speed;
        picoGo.setSpeed(speed);
        break;
      case 0x07:
        speed -= 10;
        speed = speed < 10 ? 10 : speed;
        picoGo.setSpeed(speed);
        break;
      default:
        break;
    }
    
    lasttime = millis();
  } else {
    if(millis() - lasttime > 150)
    { 
      picoGo.stop();
    }
  }
}
