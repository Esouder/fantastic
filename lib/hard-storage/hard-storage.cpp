#include "hard-storage.h"

HardStorage::Storage::Storage() {
    this->persistentStorageManager = new PersistentStorageManager(1024);
}

HardStorage::Storage::~Storage() {
    delete this->persistentStorageManager;
}

HardStorage::String::String(Storage *storage){
    persistants = new PersistentStorage<std::string>*[static_cast<int>(Stored::count)];

    PersistentStorageManager* manager = storage->persistentStorageManager;

    for(int i = 0; i < static_cast<int>(Stored::count); i++) {
        persistants[i] = new PersistentStorage<std::string>(manager);
    }
}

HardStorage::String::~String() {
    delete[] persistants;
}

std::string HardStorage::String::getStored(Stored stored) {
    return persistants[static_cast<int>(stored)]->read();
}

void HardStorage::String::setSetStored(Stored stored, std::string value) {
    persistants[static_cast<int>(stored)]->write(value);
}

HardStorage::Boolean::Boolean(Storage *storage){
    persistants = new PersistentStorage<bool>*[static_cast<int>(Stored::count)];

    PersistentStorageManager* manager = storage->persistentStorageManager;

    for(int i = 0; i < static_cast<int>(Stored::count); i++) {
        persistants[i] = new PersistentStorage<bool>(manager);
    }
}

HardStorage::Boolean::~Boolean() {
    delete[] persistants;
}

bool HardStorage::Boolean::getStored(Stored stored) {
    return persistants[static_cast<int>(stored)]->read();
}

void HardStorage::Boolean::setSetStored(Stored stored, bool value) {
    persistants[static_cast<int>(stored)]->write(value);
}