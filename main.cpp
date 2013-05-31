#include <QApplication>
#include <QDebug>
#include <QSettings>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Notability");
    QCoreApplication::setOrganizationDomain("notability.fr");
    QCoreApplication::setApplicationName("Notability");

    MainWindow *editor = MainWindow::getInstance();
    editor->show();
    return a.exec();
}
