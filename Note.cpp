#include "Note.h"

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

Editor *Note::createAndAttachEditor(MainWindow *mw)
{
    editor = this->createEditor(mw);
    return editor;
}

bool Note::isDocument() const
{
    return document;
}

void Note::setDocument(bool value)
{
    this->document = value;
}

/**
 * @brief Note::Note used to create new Note, modified = true
 * @param path
 */
Note::Note(const QString& path)
    :title(""), filePath(path), modified(true), deleted(false), document(false){}

/**
 * @brief Note::Note used to create from existing Note, modified=false
 * @param path
 * @param ti
 */
Note::Note(const QString& path, const QString& ti)
    :title(ti), filePath(path), modified(false), deleted(false), document(false){}

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
