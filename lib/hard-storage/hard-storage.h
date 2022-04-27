#ifndef HARD_STORAGE_H
#define HARD_STORAGE_H

#include  <persistent.h>

#include <string>

namespace HardStorage {

class Storage {

    friend class String;
    friend class Boolean;

    public:
        Storage();
        ~Storage();
        void commit();

    protected: 
        PersistentStorageManager *persistentStorageManager;



};

//TODO: Refactor into template. Would be much cleaner
class String {
    public:
        String(Storage *storage);
        ~String();

        enum class Stored {
            WIFI_SSID,
            WIFI_PASSWORD,
            count
        };

        std::string getStored(Stored stored);

        void setSetStored(Stored stored, std::string value);

    private:
        PersistentStorage<std::string> **persistants;

        Storage *storage;
};

class Boolean {
    public:
        Boolean(Storage *storage);
        ~Boolean();

        enum class Stored {
            BEEN_RESET,
            count
        };

        bool getStored(Stored stored);

        void setSetStored(Stored stored, bool value);

    private:
        PersistentStorage<bool> **persistants;

        Storage *storage;
};

}

#endif