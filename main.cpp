#include <QApplication>
#include <QDebug>
#include <QSettings>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    qDebug() << "hello";
    QApplication a(argc, argv);
    qDebug() << "hello";
    QCoreApplication::setOrganizationName("Notability");
    QCoreApplication::setOrganizationDomain("notability.fr");
    QCoreApplication::setApplicationName("Notability");
    qDebug() << "hello";
    MainWindow *editor = MainWindow::getInstance();
    editor->show();
    return a.exec();
}
