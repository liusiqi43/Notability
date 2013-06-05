#ifndef TRASH_H
#define TRASH_H

#include "Document.h"
#include <QSet>

class DeletedNote;

typedef QSet<Document*>::const_iterator docSetIt;
typedef QSet<DeletedNote*>::const_iterator noteSetIt;

// On fait une composition au lieu de heritage car on veut etre sur qu'un deletedNote ne soit pas traite comme les autres notes
class DeletedNote{
    Note *n;
    QSet<Document*> wasInDocuments;

public:
    DeletedNote(Note *n);
    ~DeletedNote();
    Note *getNote() const;
    void setNote(Note *value);
    docSetIt begin(){return wasInDocuments.begin();}
    docSetIt end(){return wasInDocuments.end();}
    QSet<Document *> getWasInDocuments() const;
    void setWasInDocuments(const QSet<Document *> &value);
};


class Trash
{
    QSet<DeletedNote*> deletedNotes;

    static Trash* instance;

    Trash& operator=(const Trash& t);
    Trash(const Trash& t);

    Trash();
public:
    static Trash * getInstance();
    static void releaseInstance();

    void recycle(Note *n);
    void restore(DeletedNote *n);
    void remove(DeletedNote *n);

    noteSetIt begin(){return deletedNotes.begin();}
    noteSetIt end(){return deletedNotes.end();}
};

#endif // TRASH_H
