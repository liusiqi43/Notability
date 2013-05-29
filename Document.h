#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Note.h"
#include "DocumentEditor.h"

class Document: public Note{
    QList<Note *> notes;

public:
    Document(const QString& path);
    Document(const QString& path, const QString& ti);

    QList<Note *>::const_iterator begin() const;
    QList<Note *>::const_iterator end() const;

    void addNote(Note *note);
    int count() const;
    void operator<<(Note *note);
    void removeNote(Note *note);

    const QList<Note *> &getNotes() const;
    void setNotes(const QSet<Note> &value);

    DocumentEditor *createEditor(){return new DocumentEditor(0);}
    QString exportNote(const ExportStrategy *es, unsigned int level = 0);
};


#endif // DOCUMENT_H
