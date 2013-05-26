#include "Document.h"
#include "ExportStrategy.h"
#include <QSet>

/***
 * Document
 */

Document::Document(const QString &path)
    :Note(path)
{}

Document::Document(const QString &path, const QString &ti)
    :Note(path, ti)
{}

QSet<Note *>::const_iterator Document::begin() const{
    return notes.begin();
}

QSet<Note *>::const_iterator Document::end() const{
    return notes.end();
}

void Document::addNote(Note* note)
{
    this->notes << note;
}

void Document::removeNote(Note *note)
{
    this->notes.remove(note);
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
