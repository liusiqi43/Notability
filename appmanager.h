#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QString>
#include <QDateTime>

class AppManager
{
    AppManager();

    static AppManager* instance;
public:
    static AppManager& getInstance();
    static void libererInstance();

    static const QString getWorkSpace();
};

#endif // APPMANAGER_H
