#include "PicoGo.h"


#define PIN_IR_DETECTOR_R    2
#define PIN_IR_DETECTOR_L    3
#define PIN_ULTRASONIC_TRG   14
#define PIN_ULTRASONIC_ECHO  15
#define PIN_IR               5
#define STOP                 0
#define FOWRARD              1
#define BACKWARD             2
#define RIGHT                3
#define LEFT                 4

PicoGo::PicoGo(){
}

bool PicoGo::begin(){
  motor.begin();

  pinMode(PIN_IR_DETECTOR_R, INPUT);
  pinMode(PIN_IR_DETECTOR_L, INPUT);
  pinMode(PIN_ULTRASONIC_TRG, OUTPUT);
  pinMode(PIN_ULTRASONIC_ECHO, INPUT);
  pinMode(PIN_IR, INPUT);

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

char PicoGo::IR_decode(unsigned char * code)         
{
  char value = 0;
  unsigned int count = 0;
  unsigned char i,index,cnt=0,data[4]={0,0,0,0};
  if(digitalRead(PIN_IR) == LOW)
  {
    count = 0;
    while(digitalRead(PIN_IR) == LOW && count++ < 200)   //9ms
      delayMicroseconds(60);
      
    count = 0;
    while(digitalRead(PIN_IR) == HIGH && count++ < 80)    //4.5ms
      delayMicroseconds(60);

    for(i =0;i<32;i++)
    {   
        count = 0;
        while(digitalRead(PIN_IR) == LOW && count++ < 15)  //0.56ms
            delayMicroseconds(60);
        count = 0;
        while(digitalRead(PIN_IR) == HIGH && count++ < 40)  //0: 0.56ms; 1: 1.69ms
            delayMicroseconds(60);
        if (count > 20)data[index] |= (1<<cnt);
        if(cnt == 7)
        {
          cnt = 0;
          index++;
        }
        else cnt++;
    }
    if(data[0]+data[1] == 0xFF && data[2]+data[3]==0xFF)  //check 
    {
      code[0] = data[2];
      //Serial.println(code[0], HEX);
      value = 1;
    }
    if(data[0] == 0xFF && data[1] == 0xFF && data[2] == 0xFF && data[3]==0xFF)
    {
      code[0] = 0xFF;
     // Serial.println("rep");
      value = 1;
    }
  }
  return value;
}


void PicoGo::forward(){
  motor.control(motorSpeed,motorSpeed);
  motorState = FOWRARD;
}

void PicoGo::backward(){
  motor.control(-motorSpeed,-motorSpeed);
  motorState = BACKWARD;
}

void PicoGo::right(){
  motor.control(-motorSpeed,motorSpeed);
  motorState = RIGHT;
}

void PicoGo::left(){
  motor.control(motorSpeed,-motorSpeed);
  motorState = LEFT;
}

void PicoGo::stop(){
  motor.stop();
  motorState = STOP;
}

void PicoGo::setMaxSpeed(int speed){
  maxSpeed = speed;
}

void PicoGo::setSpeed(int speed){
  motorSpeed = speed > maxSpeed ? maxSpeed : speed;
  switch(motorState){
    case FOWRARD:
      forward();
      break;
    case BACKWARD:
      backward();
      break;
    case RIGHT:
      right();
      break;
    case LEFT:
      left();
      break;
    default:
      stop();
      break;
  }
}

int PicoGo::getSpeed(){
  return motorSpeed;
}

void PicoGo::control(int right,int left){
  motor.control(right,left);
}