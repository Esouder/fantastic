#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h> 
#include <LittleFS.h>

#include "hard-storage.h"
#include "initial-setup.h"

//TODO: This should be in a different file
//TODO: And should also be settable when compiling
#define DEVICE_SERIAL 0

void setup() {
  Serial.begin(9600);
  Serial.println();

  HardStorage::Storage* storage = new HardStorage::Storage();
  HardStorage::String* storedStrings = new HardStorage::String(storage);

  //Create EEPROM data variables
  //Would be best to keep these to a minimum
  //TODO: Refactor into own class for namespace reasons.
  std::string EEPROM_WiFiSSID;// = storedStrings->getStored(HardStorage::String::Stored::WIFI_SSID);
  std::string EEPROM_WiFiPassword;// = storedStrings->getStored(HardStorage::String::Stored::WIFI_PASSWORD);

  //Start the file system:
  LittleFS.begin();

  //Attempt to connect to WiFi
  unsigned long startedAttempt = millis();
  EEPROM_WiFiSSID = "0";
  EEPROM_WiFiPassword = "0";
  Serial.println("Attempting to connect to WiFi");
  WiFi.begin(EEPROM_WiFiSSID.c_str(), EEPROM_WiFiPassword.c_str());



  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - startedAttempt > 10000) {
      WiFi.disconnect(); //Timeout after 10 seconds
      Serial.println("Could not connect to WiFi. Going to AP mode.");
      InitialSetup::SetupManager* setupManager = new InitialSetup::SetupManager();
      setupManager->startServer();
      while(true){
        if (setupManager->poll()){
          Serial.println("New setup package received.");
          Serial.println("Attempting to connect to WiFi");
          EEPROM_WiFiSSID = setupManager->getSetupPackage().ssid;
          EEPROM_WiFiPassword = setupManager->getSetupPackage().password;
          WiFi.begin(EEPROM_WiFiSSID.c_str(), EEPROM_WiFiPassword.c_str());
          setupManager->indicateFinished();
          break;
        }
        yield();
      }
    }
    yield();
  } 

  Serial.print("Connected to Wifi");

  //Do I really have to comment that all of this needs to be not in main
}

void loop() {

}

