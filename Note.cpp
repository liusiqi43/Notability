#include "Note.h"
#include "Document.h"
/***
 *  Note
 */

const QString & Note::getTitle() const {
    return title;
}

const QString & Note::getFilePath() const {
    return filePath;
}

void Note::setFilePath(const QString &p) {
    filePath = p;
    modified=true;
}

void Note::setTitle(const QString &t) {
    title = t;
    modified = true;
}

void Note::setModified(bool b) {
    modified = b;
    modified = true;
}

bool Note::isModified() const {
    return modified;
}

void Note::setDeleted(bool b) {
    deleted = b;
    modified = true;
}

bool Note::isDeleted() const {
    return deleted;
}

Editor *Note::createAndAttachEditor()
{
    editor = this->createEditor();
    return editor;
}

bool Note::isDocument() const
{
    return type == document;
}

nListIt Note::begin() const
{
    if(isDocument())
        return dynamic_cast<const Document*>(this)->begin();
    else
        return 0;
}

nListIt Note::end() const
{
    if(isDocument())
        return dynamic_cast<const Document*>(this)->end();
    else
        return 0;
}

/**
 * @brief Note::Note used to create new Note, modified = true
 * @param path
 */
Note::Note(const QString& path)

    :title("New Note"), filePath(path), modified(true), deleted(false){}
/**
 * @brief Note::Note used to create from existing Note, modified=false
 * @param path
 * @param ti
 */
Note::Note(const QString& path, const QString& ti)
    :title(ti), filePath(path), modified(false), deleted(false){}

Note::~Note()
{
    qDebug()<<"Destruction of "<<this->getTitle();
    for(QSet<Document*>::const_iterator it = inDocuments.begin(); it!=inDocuments.end(); ++it){
        (*it)->removeNote(this);
    }
}

bool Note::operator ==(const Note &other)
{
    return this->getFilePath()==other.getFilePath();
}

Editor *Note::getEditor() const
{
    return editor;
}

void Note::setEditor(Editor *value)
{
    editor = value;
}

void Note::addToDocument(Document *doc)
{
    inDocuments << doc;
    qDebug()<<"Note: "<<this->getTitle()<<" Added to: "<<doc->getTitle();

    qDebug()<<"==========";
    for(QSet<Document*>::const_iterator it = inDocuments.begin(); it!=inDocuments.end(); ++it){
        qDebug()<<this->title<<" included in: "<<doc->getTitle();
    }
    qDebug()<<"==========";
}

void Note::removeFromDocument(Document *doc)
{
    inDocuments.remove(doc);
}

bool Note::belongs(Document *doc)
{
    return inDocuments.contains(doc);
}

QSet<Document *> Note::getInDocuments() const
{
    return inDocuments;
}

void Note::setInDocuments(const QSet<Document *> &value)
{
    inDocuments = value;
}
