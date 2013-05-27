#ifndef DOCUMENTEDITOR_H
#define DOCUMENTEDITOR_H

#include "Editor.h"
class Document;

class DocumentEditor : public Editor
{
    Q_OBJECT
public:
    explicit DocumentEditor(Document* doc, QWidget *parent=0);

signals:

public slots:
    void BACKEND_SET_CONTENT();

private:
    QString currentDocString;
};

#endif // DOCUMENTEDITOR_H
