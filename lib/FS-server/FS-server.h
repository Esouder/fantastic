#ifndef FS_SERVER_H
#define FS_SERVER_H

#include <ESP8266WebServer.h>
#include <LittleFS.h>

#include <vector>
#include <string>

namespace FSServer {

    class FSServer {

        public:
            FSServer(String root, int port);
            ~FSServer();

            void startServer();
            void handleClient();

            void on(std::string path, std::function<void(void)> handler);
            void on(std::string path, HTTPMethod method, std::function<void(void)> handler);

            bool hasArg(std::string arg);

            std::string arg(std::string arg);

        private:
            String root;
            ESP8266WebServer *server;
            
            void handleNotFound();

    };


}

#endif