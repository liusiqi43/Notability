#include "DocumentEditor.h"
#include "Document.h"
#include <QWidget>

DocumentEditor::DocumentEditor(Document* doc, QWidget *parent)
    :Editor(doc, parent)
{
}

void DocumentEditor::BACKEND_SET_CONTENT()
{
}
