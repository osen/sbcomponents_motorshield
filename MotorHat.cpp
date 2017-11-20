#include "MotorHat.h" 

#include <exception>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

Adafruit_DCMotor::Adafruit_DCMotor(Adafruit_MotorHAT* _hat, int num) {
    hat = _hat;
	motornum = num;
	
	PWM = 0;
	IN1 = 0;
	IN2 = 0;
	AR1 = 0;
	AR2 = 0;
	if (num == 0) {
		PWM = 11;
		IN1 = 15;
		IN2 = 13;
		AR1 = 37;
		AR2 = 33;
	} else if (num == 1) {
		PWM = 22;
		IN1 = 16;
		IN2 = 18;
		AR1 = 35;
		AR2 = 36;
	} else if (num == 2) {
		PWM = 19;
		IN1 = 21;
		IN2 = 23;
		AR1 = 37;
		AR2 = 33;
	} else if (num == 3) {
		PWM = 32;
		IN1 = 24;
		IN2 = 26;
		AR1 = 35;
		AR2 = 36;
	} else throw "MotorHAT Motor must be between 0 and 3 inclusive";

	pinMode(PWM, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(AR1, OUTPUT);
	pinMode(AR2, OUTPUT);

	softPwmCreate(PWM, 0, 100);
	//softPwmWrite(PWM, 100);

	digitalWrite(PWM, HIGH);
	digitalWrite(IN1, HIGH);
	digitalWrite(IN2, LOW);
	digitalWrite(AR1, LOW);
	digitalWrite(AR2, LOW);
}

void Adafruit_DCMotor::run(Direction dir) {
	if ( dir == FORWARD) {
		hat->setPin(IN2,0);
		hat->setPin(IN1,1);
		hat->setPin(AR1,1);
		hat->setPin(AR2,0);
	}
	if ( dir == BACKWARD) {
		hat->setPin(IN1,0);
		hat->setPin(IN2,1);
		hat->setPin(AR1,0);
		hat->setPin(AR2,1);
	}
	if ( dir == RELEASE) {
		setSpeed(0);
		hat->setPin(IN1,0);
		hat->setPin(IN2,0);
		hat->setPin(AR1,0);
		hat->setPin(AR2,0);
	}
}

void Adafruit_DCMotor::setSpeed(int speed) {
	if (speed < 0) {
		speed = 0;
	}
	if (speed > 255) {
		speed = 255;
	}

	int val = ((float)speed / 255.0f) * 100.0f;

	softPwmWrite(PWM, val);
}

Adafruit_MotorHAT::Adafruit_MotorHAT() {
	//wiringPiSetupGpio();
	wiringPiSetupPhys();

	for(int idx = 0; idx < 4; idx++) {
		dcs.push_back(Adafruit_DCMotor(this, idx));
	}
}

void Adafruit_MotorHAT::setPin(int pin, int value) {
	if ((pin < 0)) {
		throw "PWM pin must be greater than 0";
        }
	if ((value != 0) && (value != 1)) {
		throw "Pin value must be 0or 1!";
        }
	if (value == 0) {
		digitalWrite(pin, LOW);
        }
	if (value == 1) {
		digitalWrite(pin, HIGH);
        }
}

Adafruit_DCMotor& Adafruit_MotorHAT::getDC(int num) {
	if ((num < 1) || (num > 4))
		throw "MotorHAT DC must be between 1 and 4 inclusive";
	return dcs[num-1];
}

void Adafruit_MotorHAT::resetAll() {
	for(int idx = 0; idx < dcs.size(); idx++)
	{
		softPwmWrite(dcs.at(idx).PWM, 0);
	}
}

