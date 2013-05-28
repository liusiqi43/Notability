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

void Document::addNote(Note* note)
{
    this->notes << note;
}

void Document::operator <<(Note *note)
{
    this->addNote(note);
}

void Document::removeNote(Note *note)
{
    this->notes.removeOne(note);
}

//DocumentEditor* Document::createEditor(){
//    return new DocumentEditor(this);
//}

QString Document::exportNote(const ExportStrategy *es, unsigned int level)
{
    if(level){
        return es->exportNote(this, level);
    }
    else{
        return es->header()+es->exportNote(this)+es->footer();
    }
}
