#include <QApplication>
#include <QDebug>
#include "mainUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainUI editor;
    editor.show();
    return a.exec();
}
