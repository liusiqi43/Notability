#include "AppManager.h"

const QString AppManager::generateID(){
    QDateTime t = QDateTime::currentDateTime();
    return t.toString("yyyyMMddzzzssmmhh");
}

const QString AppManager::getWorkSpace(){
    return "./Ressources";
}

AppManager::AppManager(){}

AppManager* AppManager::instance = 0;
AppManager &AppManager::getInstance(){
    if (!instance)
        instance = new AppManager;
    return *instance;
}

void AppManager::libererInstance(){
    if (instance)
        delete instance;
    instance=0;
}
