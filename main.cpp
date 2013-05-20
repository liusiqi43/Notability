#include <QApplication>
#include <QWidget>

#include "mainUI.h"
#include "Notes.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainUI editor;
    editor.show();
//    ArticleEditor * editor = new ArticleEditor(art);
//    editor->show();
    return a.exec();
}
