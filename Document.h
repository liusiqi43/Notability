#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Note.h"
#include "DocumentEditor.h"

typedef QList<Note *>::const_iterator nListIt;

class Document: public Note{
    QList<Note *> notes;

public:
    Document(const QString& path);
    Document(const QString& path, const QString& ti);
    ~Document();

    nListIt begin() const;
    nListIt end() const;
    Note* & last();

    bool contains(Note *n) const;

    void addNote(Note *note) throw (NotesException);
    int count() const;

    void removeNote(Note *note, bool twoway = true);
    Note* find(const QString& filepath);

    const QList<Note *> &getNotes() const;
    void setNotes(const QSet<Note> &value);

    DocumentEditor *createEditor(){return new DocumentEditor(this);}
    QString exportNote(const ExportStrategy *es, unsigned int level = 0);


    class DepthFirstIterator{
        bool finished;
        Document* currentDoc;
        QList<Document*> previousDocs;
        QList<nListIt> previousDocIters;
        nListIt currentDocIter;
        Note* nextNote;

        Note* getNextNote();
    public:
        // prefix
        DepthFirstIterator & operator++();
        Note* operator*();
        bool isDone();
        DepthFirstIterator(Document *);

    };

    DepthFirstIterator &beginDFIterator();
};


#endif // DOCUMENT_H
