#include "PicoGo.h"

PicoGo picoGo;

void setup() {
  picoGo.begin();
  picoGo.stop();
}

void loop() {
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
    LGFX_Sprite* cv = picoGo.getCanvas();
    cv->fillScreen(TFT_BLACK);
    cv->setCursor(0, 0);
    cv->printf("リモコンコード：0x%02X\n",results);
    cv->printf("スピード：%d\n",speed);
    cv->pushSprite(0, 0);
    
    lasttime = millis();
  } else {
    if(millis() - lasttime > 150)
    { 
      picoGo.stop();
    }
  }
}