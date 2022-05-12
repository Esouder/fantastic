#ifndef INITIAL_SETUP_H
#define INITIAL_SETUP_H

#include "FS-server.h"

#include <DNSserver.h>

#include <string>


namespace InitialSetup {

class SetupManager {

    public:

        //package of wifi setup data
        struct SetupPackage {
            std::string ssid;
            std::string password;
        };

        //Constructors/Destructors
        SetupManager();
        ~SetupManager();

        //Starts the setup server
        void startServer();
        //Runs the setup server. Returns true if there's a new setup package to use; false otherwise.
        bool poll();
        //Returns the setup package.
        SetupPackage getSetupPackage();
        //allows other code to indicate wheather or not the setup was sucessful
        void indicateFinished();

        
    private:
        FSServer::FSServer* setupServer;

        DNSServer dnsServer;

        SetupPackage currentSetupPackage;
        bool newSetupPackage; //true means there is a new setup package to use
        bool internalSuccessFlag = false;

        //Handlers
        void handleSetupSubmit();

};

}

#endif