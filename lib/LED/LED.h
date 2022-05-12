#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <Arduino.h>

namespace LED {

    enum class Location{
        BUILTIN,
        FANBOARD,
        //magic line do not cross
        count
        };

    enum class Mode{
        ON,
        OFF,
        FLASH_ONCE,
        BLINK_SLOW,
        BLINK_FAST,
    };

    class LED {

        public:
            LED(Location location, bool inverted = false);
            ~LED();
            void setMode(Mode mode);
            void poll();

        private:
            static const constexpr uint8_t ports[] = {
                2,
                15
            };

            uint8_t port;
            Mode mode;
            bool inverted;

            union {
                struct {
                    bool flashStarted;
                    unsigned long flashOnMark;
                } flashInfo;
                struct {
                    bool blinkStarted;
                    bool blinkOn;
                    unsigned long blinkChangeMark;
                } blinkInfo;
            } modeInfo;
    };
}


#endif