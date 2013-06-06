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

Note* & Document::last()
{
    return notes.last();
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
        if(static_cast<Document*>(note)->find(this->getFilePath()))
            // circular inclusion!
            throw NotesException("Cowardly refused your request...If you want to add A into B, this means that B is already included in A! Think twice...");
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

void Document::removeNote(Note *note)
{
    this->notes.removeOne(note);
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

Document::DepthFirstIterator Document::beginDFIterator()
{
    Document::DepthFirstIterator it(this);
    return it;
}

Document::DepthFirstIterator & Document::DepthFirstIterator::operator++()
{
//    qDebug()<<"Compare: " << (*currentDocIter)->getTitle();
//    qDebug()<< " to " << (*static_cast<Document *>(currentDoc)->end())->getTitle();
//    if(*currentDocIter != static_cast<Document *>(currentDoc)->last() && !(*currentDocIter)->isDocument()){
//        ++currentDocIter;
//    } else if ((*currentDocIter)->isDocument()) {
//        qDebug()<<"currentIsADocument";
//        previousDocs.push_back(currentDoc);
//        currentDoc = *currentDocIter;
//        previousDocIters.push_back(currentDocIter);
//        currentDocIter = static_cast<Document *>(currentDoc)->begin();
//    } else {
//        throw NotesException("Bizarre!");
//    }

//    if (*currentDocIter == static_cast<Document *>(currentDoc)->last() && !(*currentDocIter)->isDocument()){
//            if(previousDocs.size()<=1){
//                qDebug()<<"Finished...";
//                //finished
//                finished = true;
//            } else {
//                qDebug()<<"Restoring...";
//                // restore
//                currentDoc = previousDocs.last();
//                qDebug()<<"New currentDoc:"<<currentDoc->getTitle();
//                previousDocs.pop_back();
//                currentDocIter = ++previousDocIters.last();
//                previousDocIters.pop_back();
//            }
//    }

    /*if((*currentDocIter)->isDocument())
        return deploy(dynamic_cast<Document*>(*currentDocIter));
    else{

    }*/

    if(nextNote==0){
        nextNote=getNextNote();
    }
    return *this;
}

Note *Document::DepthFirstIterator::operator*()
{
    return nextNote;
}

bool Document::DepthFirstIterator::isDone()
{
    return finished;
}

Note * Document::DepthFirstIterator::getNextNote(){
    while(*currentDocIter!=currentDoc->last()){
        if((*currentDocIter)->isDocument()){
            previousDocs.push_back(static_cast<Document*>(*currentDocIter));
            nListIt lastIter(currentDocIter);
            previousDocIters.push_back(lastIter);
            currentDocIter = static_cast<Document*>(*currentDocIter)->begin();
        }
        else {
            ++currentDocIter;
            return *currentDocIter;
        }
    }

    while(!previousDocs.isEmpty()){
        currentDoc = previousDocs.first();
        currentDocIter = previousDocIters.first();
        previousDocs.pop_front();
        previousDocIters.pop_front();

        Note* note = getNextNote();
        if(note!=0)
            return note;
    }

    finished = true;
    return 0;
}

Document::DepthFirstIterator::DepthFirstIterator(Document * doc)
{
    finished = false;
    currentDoc = doc;
    currentDocIter = doc->begin();
}
