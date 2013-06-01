#include "DocumentEditor.h"
#include "Document.h"
#include <QWidget>

DocumentEditor::DocumentEditor(Document* doc, QWidget *parent)
    :Editor(doc, parent)
{
    for(QList<Note*>::const_iterator it = doc->begin(); it != doc->end(); ++it){
            contentLayout->addWidget((*it)->createAndAttachEditor());
    }
}

void DocumentEditor::BACKEND_SET_CONTENT()
{
}
