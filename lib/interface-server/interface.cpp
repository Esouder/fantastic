#include "interface.h"

Interface::Interface::Interface(Controller::FanController *fanController) {
    this->server = new FSServer::FSServer("/main", 80);
    this->domainName = "fantastic";
    this->fanController = fanController;
}

Interface::Interface::~Interface() {
    delete this->server;
}

void Interface::Interface::start() {
    MDNS.begin(this->domainName); //TODO: Error checking

    //config server
    // something like: server -> on("/main", HTTP_GET, [this](){handleMain();});
    server -> on("/fan-on", HTTP_POST, [this](){fanController->enable();});
    server -> on("/fan-off", HTTP_POST, [this](){fanController->disable();});
    server -> startServer();
}

bool Interface::Interface::poll() {
    server -> handleClient();

    return MDNS.update();
}


