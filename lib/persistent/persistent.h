#ifndef PERSISTENT_H
#define PERSISTENT_H

#include <EEPROM.h>

class PersistentStorageManager {

    template<typename> friend class PersistentStorage;

    public:
        PersistentStorageManager(int EEPROMSize);
        ~PersistentStorageManager();

        void commit();

    protected:
        int EEPROMAllocated; 

};

template <typename T> class PersistentStorage {

    public:

        PersistentStorage(PersistentStorageManager *manager){
            this->manager = manager;
        }

        bool initialize(){
            if(manager->EEPROMAllocated + sizeof(T) < EEPROM.length()){
                this->address = manager->EEPROMAllocated;
                manager->EEPROMAllocated += sizeof(T);
                return true;
            }

            return false;
        }
        
        void write(T object){
            EEPROM.put(this->address, object);
        }

        T read(){
            T object;
            EEPROM.get(this->address, object);
            return object;
        }
        

    private:

        int address;
        PersistentStorageManager *manager;
};

#endif