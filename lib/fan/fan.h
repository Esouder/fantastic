#ifndef FAN_H
#define FAN_H

#include <stdint.h>
#include <Arduino.h>

#include "LED.h"
namespace Controller {

    class FanController {

        public:
            FanController(LED::LED* led);
            ~FanController();

            bool poll();

            void setSpeed(int speedPct, bool enableIfNot = false);

            void enable();
            void disable();

            uint8_t getSpeed();
            bool getEnabled();
            bool getStatus();



        private:

            static uint8_t scalePWMOutput(uint8_t speedPct);

            uint8_t speedPct;
            bool enabled;
            bool statusGood;
            LED::LED* led;

            uint8_t pwmPin;
            uint8_t enablePin;
            uint8_t statusPin;

    };
}
#endif