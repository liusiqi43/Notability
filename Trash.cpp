#include "Trash.h"
#include "mainwindow.h"


Trash* Trash::instance = 0;

Trash::Trash()
{
}

void Trash::releaseInstance(){
    if(instance)
        delete instance;
    instance = 0;
}

void Trash::recycle(Note *n)
{
    DeletedNote * dn = new DeletedNote(n);
    // store all
    dn->setWasInDocuments(n->getInDocuments());

    // remove all relationships between notes and docs.
    for(QSet<Document*>::ConstIterator it = n->beginInDoc(); it!=n->endInDoc(); ++it){
        (*it)->removeNote(n);
    }
    n->setDeleted(true);
    deletedNotes.insert(dn);
    MainWindow::getInstance()->updateSideBar();
}

void Trash::restore(DeletedNote *n)
{
    for(docSetIt it = n->begin(); it!=n->end(); ++it){
        if((*it))
            (*it)->addNote(n->getNote());
    }
    n->getNote()->setInDocuments(n->getWasInDocuments());
    n->getNote()->setDeleted(false);
    MainWindow::getInstance()->updateSideBar();
    deletedNotes.remove(n);
}

void Trash::remove(DeletedNote *n)
{
    QFile::remove(n->getNote()->getFilePath());
    deletedNotes.remove(n);
    delete n;
}


Trash *Trash::getInstance()
{
    if(!instance)
        instance = new Trash;
    return instance;
}



DeletedNote::DeletedNote(Note *note):n(note)
{}

DeletedNote::~DeletedNote()
{

}

Note *DeletedNote::getNote() const
{
    return n;
}

void DeletedNote::setNote(Note *value)
{
    n = value;
}

QSet<Document *> DeletedNote::getWasInDocuments() const
{
    return wasInDocuments;
}

void DeletedNote::setWasInDocuments(const QSet<Document *> &value)
{
    wasInDocuments = value;
}
