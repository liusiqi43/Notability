#ifndef DOCUMENTEDITOR_H
#define DOCUMENTEDITOR_H

#include "Editor.h"
class Document;

class DocumentEditor : public Editor
{
public:
    DocumentEditor(Document* doc, QWidget *parent);
};

#endif // DOCUMENTEDITOR_H
