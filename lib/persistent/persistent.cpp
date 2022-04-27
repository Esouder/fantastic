#include "persistent.h"

PersistentStorageManager::PersistentStorageManager(int EEPROMSize) {
    this->EEPROMAllocated = 0;
    EEPROM.begin(EEPROMSize);
}

PersistentStorageManager::~PersistentStorageManager() {
    EEPROM.end();
}

void PersistentStorageManager::commit() {
    EEPROM.commit();
}
