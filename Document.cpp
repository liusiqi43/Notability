#include "Document.h"
#include "ExportStrategy.h"
#include <QList>

/***
 * Document
 */

Document::Document(const QString &path)
    :Note(path, "New Document")
{
    setDocument(true);
}

Document::Document(const QString &path, const QString &ti)
    :Note(path, ti)
{
    setDocument(true);
}

QList<Note *>::const_iterator Document::begin() const{
    return notes.begin();
}

QList<Note *>::const_iterator Document::end() const{
    return notes.end();
}

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

void Document::addNote(Note* note)
{
    this->notes << note;
    setModified(true);
}

int Document::count() const
{
    return notes.count();
}

void Document::operator <<(Note *note)
{
    this->addNote(note);
}

void Document::removeNote(Note *note)
{
    this->notes.removeOne(note);
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
