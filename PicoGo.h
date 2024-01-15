#include <LovyanGFX.hpp>
#include "Motor.h"

class LGFX_ST7789 : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789    _panel_instance;
  lgfx::Bus_SPI         _bus_instance;

  public:
    LGFX_ST7789() {
      {
        auto cfg = _bus_instance.config();
        cfg.spi_host    = 1;
        cfg.spi_mode    = 0;
        cfg.freq_write  = 8000000; 
        cfg.freq_read   = 8000000;
        cfg.pin_mosi    = 11;
        cfg.pin_miso    = -1;   
        cfg.pin_sclk    = 10;
        cfg.pin_dc      = 8;

        _bus_instance.config(cfg);
        _panel_instance.setBus(&_bus_instance);
      }
      {
        auto cfg = _panel_instance.config();
        cfg.pin_cs  = 9;
        cfg.pin_rst = 12;
        cfg.panel_width  = 135;
        cfg.panel_height = 240;
        cfg.offset_x = 52;
        cfg.offset_y = 40;
        cfg.readable = false;
        cfg.rgb_order = false;
        cfg.invert = true;
        cfg.offset_rotation = 1;

        _panel_instance.config(cfg);
      }
      setPanel(&_panel_instance);
    }
};

class PicoGo {
public:
  PicoGo();
  bool begin();
  LGFX_Sprite* getCanvas();
  bool getIrDetectorRight();
  bool getIrDetectorLeft();
  int getUltrasonicDistance();
  char IR_decode(unsigned char * code);
  void forward();
  void backward();
  void right();
  void left();
  void stop();
  void setMaxSpeed(int speed);
  void setSpeed(int speed);
  int getSpeed();
  void control(int right,int left);
private:
  LGFX_ST7789 lcd;
  LGFX_Sprite* canvas;
  Motor motor;
  int motorSpeed = 100;
  int maxSpeed = 100;
  int motorState;
};