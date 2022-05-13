#ifndef INTRFACE_H
#define INTRFACE_H

#include "FS-server.h"
#include "fan.h"

#include <esp8266mDNS.h>


namespace Interface {

    class Interface {

        public:

            Interface(Controller::FanController* fanController);
            ~Interface();

            void start();

            bool poll();

        private:
            Controller::FanController* fanController;
            FSServer::FSServer *server;
            String domainName;

    };
}

#endif