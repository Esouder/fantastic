#include "fan.h"

#define FAN_PWM_PIN 14
#define FAN_ENABLE_PIN 4
#define FAN_STATUS_PIN 5

#define FAN_MIN_PWM_PCT 65
#define FAN_MAX_PWM_PCT 100

Controller::FanController::FanController(LED::LED* led) {
    this -> pwmPin = FAN_PWM_PIN;
    this -> enablePin = FAN_ENABLE_PIN;
    this -> statusPin = FAN_STATUS_PIN;
    this -> led = led;
    pinMode(pwmPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    pinMode(statusPin, INPUT);
}

uint8_t Controller::FanController::scalePWMOutput(uint8_t speedPct) {
    return map(speedPct, FAN_MIN_PWM_PCT, FAN_MAX_PWM_PCT, 0, 255);
}

bool Controller::FanController::poll() {
    if(this -> enabled) {
        analogWrite(this -> pwmPin, scalePWMOutput(this -> speedPct));
        digitalWrite(this -> enablePin, HIGH);
    } else {
        digitalWrite(this -> pwmPin, LOW);
        digitalWrite(this -> enablePin, LOW);
    }

    this -> statusGood = digitalRead(this -> statusPin);

    return this -> statusGood;
}

void Controller::FanController::setSpeed(int speedPct, bool enableIfNot) {
    this -> speedPct = speedPct;
    if(enableIfNot) {
        this -> enable();
    }
}

void Controller::FanController::enable() {
    this -> enabled = true;
    led -> setMode(LED::Mode::FLASH_ONCE);
    Serial.println("Fan enabled");
}

void Controller::FanController::disable() {
    this -> enabled = false;
    led -> setMode(LED::Mode::FLASH_ONCE);
    Serial.println("Fan disabled");
}

uint8_t Controller::FanController::getSpeed() {
    return this -> speedPct;
    Serial.print("Fan speed set to ");
    Serial.println(this -> speedPct);
}

bool Controller::FanController::getEnabled() {
    return this -> enabled;
}

bool Controller::FanController::getStatus() {
    return this -> statusGood;
}