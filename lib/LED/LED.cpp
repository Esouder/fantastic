#include "LED.h"

#define FLASH_DURATION_MS 500
#define BLINK_SLOW_DURATION_MS 750
#define BLINK_FAST_DURATION_MS 250

LED::LED::LED(Location location, bool inverted) {
    this->port = ports[static_cast<int>(location)];
    this->inverted = inverted;
    pinMode(port, OUTPUT);
}

void LED::LED::poll() {
    switch (this->mode) {
        case Mode::ON:
            digitalWrite(this->port, !this->inverted);
            break;
        case Mode::OFF:
            digitalWrite(this->port, this->inverted);
            break;
        case Mode::FLASH_ONCE:
            if(this->modeInfo.flashInfo.flashStarted){
                if(millis() - this->modeInfo.flashInfo.flashOnMark > FLASH_DURATION_MS){
                    digitalWrite(this->port, this->inverted);
                }
            } else {
                digitalWrite(this->port, !this->inverted);
                this->modeInfo.flashInfo.flashOnMark = millis();
                this->modeInfo.flashInfo.flashStarted = true;
            }
            break;
        case Mode::BLINK_SLOW:
        case Mode::BLINK_FAST:
            if(this->modeInfo.blinkInfo.blinkStarted){
                if(millis() - this->modeInfo.blinkInfo.blinkChangeMark > ((this->mode == Mode::BLINK_FAST) ? BLINK_FAST_DURATION_MS : BLINK_SLOW_DURATION_MS)){
                    switch (this->modeInfo.blinkInfo.blinkOn) {
                        case true:
                            digitalWrite(this->port, this->inverted);
                            break;
                        case false:
                            digitalWrite(this->port, !this->inverted);
                            break;
                    }
                    this->modeInfo.blinkInfo.blinkChangeMark = millis();
                    this->modeInfo.blinkInfo.blinkOn = !this->modeInfo.blinkInfo.blinkOn;
                }
            } else {
                digitalWrite(this->port, !this->inverted); //blinks always start on
                this->modeInfo.blinkInfo.blinkOn = true;
                this->modeInfo.blinkInfo.blinkChangeMark = millis();
                this->modeInfo.blinkInfo.blinkStarted = true;
            }
            break;
    }
}

void LED::LED::setMode(Mode mode) {
    this->mode = mode;
    switch (this->mode) {
        case Mode::FLASH_ONCE:
            this->modeInfo.flashInfo.flashStarted = false;
            break;
        case Mode::BLINK_SLOW:
        case Mode::BLINK_FAST:
            this->modeInfo.blinkInfo.blinkStarted = false;
            break;
        default:
            //do nothing, no mode info to clear
            break;
    }
}