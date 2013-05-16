#include <QApplication>
#include <QWidget>

#include "NotesEditor.h"
#include "Notes.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NotesEditor editor;
    editor.show();
//    ArticleEditor * editor = new ArticleEditor(art);
//    editor->show();
    return a.exec();
}
