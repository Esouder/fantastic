#include "initial-setup.h"

#define DNS_PORT 53

InitialSetup::SetupManager::SetupManager() {
    this->setupServer = new FSServer::FSServer("/setup", 80);
    this->currentSetupPackage = SetupPackage();
    this->internalSuccessFlag = false;
    this->newSetupPackage = false;
}

InitialSetup::SetupManager::~SetupManager() {
    delete this->setupServer;
}

void InitialSetup::SetupManager::startServer(){
    
    
    std::string APSSID = "Fantastic"; //TODO: Make this unique
    WiFi.mode(WIFI_AP_STA);
    WiFi.channel(4);
    WiFi.softAP(APSSID.c_str());

    Serial.print("IP addr: ");
    Serial.println(WiFi.softAPIP());

    //configure DNS server
    //Redirect all names to ourselves
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
    
    //configure server
    setupServer->on("/setup-submit", HTTP_POST, [this](){handleSetupSubmit();});
    setupServer->startServer();

}

bool InitialSetup::SetupManager::poll(){
    if(!this->internalSuccessFlag){
        dnsServer.processNextRequest();
        setupServer->handleClient();
        if(this->newSetupPackage){
            this->newSetupPackage = false;
            return true;
        }
        return false;
    } else {
        dnsServer.stop();
        WiFi.softAPdisconnect(true);
        delete this;
        return true;
    }
    
}

void InitialSetup::SetupManager::handleSetupSubmit(){
    if(this->setupServer->hasArg("ssid") && this->setupServer->hasArg("password")){
        this->currentSetupPackage.ssid = this->setupServer->arg("ssid");
        this->currentSetupPackage.password = this->setupServer->arg("password");
        this->newSetupPackage = true;
    }
}

InitialSetup::SetupManager::SetupPackage InitialSetup::SetupManager::getSetupPackage(){
    return this->currentSetupPackage;
}

void InitialSetup::SetupManager::indicateFinished(){
    this->internalSuccessFlag = true;
}

