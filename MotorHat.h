#include <wiringPi.h>
#include <softPwm.h>

#include <vector>

enum Direction {
   FORWARD,
   BACKWARD,
   BRAKE,
   RELEASE
};

enum Style {
 SINGLE,
 DOUBLE,
 INTERLEAVE,
 MICROSTEP
};

class Adafruit_MotorHAT; 

class Adafruit_DCMotor {
public:
  Adafruit_DCMotor(Adafruit_MotorHAT* _hat, int num); 
  Adafruit_MotorHAT* hat;

  int PWM;
  int IN2;
  int IN1;
  int AR1;
  int AR2;

  int motornum;

  void run(Direction dir);

  void setSpeed(int speed);

};

class Adafruit_MotorHAT {
public:
  std::vector<Adafruit_DCMotor> dcs;

  Adafruit_MotorHAT();

  void setPin(int pin, int value);

  Adafruit_DCMotor& getDC(int num);
  void resetAll();
};

