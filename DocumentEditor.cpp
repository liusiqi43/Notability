#include "DocumentEditor.h"
#include "Document.h"
#include <QWidget>

DocumentEditor::DocumentEditor(Document* doc, MainWindow *mw, QWidget *parent)
    :Editor(doc, mw, parent)
{
}

void DocumentEditor::BACKEND_SET_CONTENT()
{
}
