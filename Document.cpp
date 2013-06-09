#include "Document.h"
#include "ExportStrategy.h"
#include "NotesManager.h"
#include <QList>

/***
 * Document
 */

Document::Document(const QString &path)
    :Note(path, "New Document")
{
    qDebug()<<"Created Document";
    type = document;
}

Document::Document(const QString &path, const QString &ti)
    :Note(path, ti)
{
    qDebug()<<"Created Document with title";
    type = document;
}

Document::~Document(){
    qDebug()<<"Destruction of doc "<<this->getTitle();
    for(nListIt it = begin(); it!=end(); ++it){
        (*it)->removeFromDocument(this);
    }
}

nListIt Document::begin() const{
    return notes.begin();
}

nListIt Document::end() const{
    return notes.end();
}

// A shallow test of containing
bool Document::contains(Note *n) const
{
    return notes.contains(n);
}

// a deep find
Note* Document::find(const QString& filepath){
    for(QList<Note *>::const_iterator it = begin(); it!= end(); ++it){
        //        qDebug()<<"Comparing:"<<(*it)->getFilePath()<<" & "<<filepath;
        if((*it)->getFilePath() == filepath)
        {
            return *it;
        }
        else if((*it)->isDocument()){
            Note* result = dynamic_cast<Document*>(*it)->find(filepath);
            if(result) return result;
        }
    }
    return 0;
}

void Document::addNote(Note* note) throw (NotesException)
{
    // Document-document case, test if there is a circular inclusion
    if(note->isDocument()){
        if(static_cast<Document*>(note)->find(this->getFilePath())){
            qDebug()<<"Circular" << this->getTitle();
            // circular inclusion!
            throw NotesException("Cowardly refused your request...If you want to add A into B, this means that B is already included in A! Think twice...");
        }
    }
    this->notes << note;
    note->addToDocument(this);
    qDebug()<<"Doc:"<<this->getTitle()<<" has "<< this->notes.count() << " notes";
    setModified(true);
}

int Document::count() const
{
    return notes.count();
}

void Document::removeNote(Note *note, bool twoway)
{
    this->notes.removeOne(note);
    if(twoway)
        note->removeFromDocument(this);
    this->setModified(true);
}

QString Document::exportNote(const ExportStrategy *es, unsigned int level)
{
    if(level){
        return es->exportNote(this, level);
    }
    else{
        return es->header()+es->exportNote(this)+es->footer();
    }
}

Document::DepthFirstIterator& Document::beginDFIterator()
{
    Document::DepthFirstIterator *it = new Document::DepthFirstIterator(this);
    return *it;
}

bool Document::DepthFirstIterator::hasNext() const
{
    return !fringe.empty();
}

Note * Document::DepthFirstIterator::next(){
    if(!hasNext())
        throw NotesException("Tree ran out of elements");
    Note *node = fringe.takeFirst();
    if(node->isDocument()){
        for (nListIt it = node->begin(); it!=node->end(); ++it){
            if(!explored.contains(*it)){
                fringe.push_back(*it);
                explored << *it;
            }
        }
    }
    return node;
}

Document::DepthFirstIterator::DepthFirstIterator(Document * const doc)
{
    if(doc)
        fringe.push_back(doc);
}
