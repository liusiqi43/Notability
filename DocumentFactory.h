#ifndef DOCUMENTFACTORY_H
#define DOCUMENTFACTORY_H

#include "NoteFactory.h"
#include "Document.h"

class DocumentFactory : public NoteFactory
{
public:
    Document* buildNewNote();
    Document* buildNote(const QString &path);
    Document* buildNoteCopy(const Document &note);
    QString getFolder();
    QString getExtension();
};

#endif // DOCUMENTFACTORY_H
