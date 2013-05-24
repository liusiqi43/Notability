#include <fstream>
#include <QFile>
#include <QDebug>

#include <QString>
#include <QTextStream>

#include "NotesManager.h"
#include "AppManager.h"
#include "Notes.h"
#include "Editors.h"

/***
 * NotesException
 */
NotesException::NotesException(const QString& message):info(message){}
QString NotesException::getInfo() const { return info; }

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

void Note::setTitle(QString &t) {
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

/**
 * @brief Note::Note used to create new Note, modified = true
 * @param path
 */
Note::Note(const QString& path)
    :title(""), deleted(false), modified(true){}

/**
 * @brief Note::Note used to create from existing Note, modified=false
 * @param path
 * @param ti
 */
Note::Note(const QString& path, const QString& ti)
    :title(ti), deleted(false), modified(false), filePath(path){}

const QString &Note::exportNote(ExportStrategy *es, unsigned int level)
{
    if(level){
        return es->exportNote(this, level);
    }
    else{
        return es->header()+es->exportNote(this)+es->footer();
    }
}

/***
 *  Article
 */

Article::Article(const QString& path):
    Note(path),text("") {}

Article::Article(const QString& path, const QString& ti, const QString& te):
    Note(path, ti),text(te) {}

const QString& Article::getText() const { return text; }

void Article::setText(const QString& t) {
    setModified(true);
    text=t;
}

ArticleEditor *Article::createEditor()
{
    return new ArticleEditor(this);
}

/***
 * Binary
 */

Binary::Binary(const QString& path)
    :Note(path), description(""), mediaPath("")
{}
Binary::Binary(const QString& path, const QString& ti, const QString& des, const QString& media)
    :Note(path, ti), description(des), mediaPath(media)
{}

QString Binary::getDescription() const
{
    return description;
}

void Binary::setDescription(const QString &value)
{
    this->setModified(true);
    description = value;
}

QString Binary::getMediaPath() const
{
    return mediaPath;
}

void Binary::setMediaPath(const QString &value)
{
    this->setModified(true);
    mediaPath = value;
}

/***
 * AudioNote
 */
AudioNote::AudioNote(const QString& ti, const QString& des, const QString& aPath, Document *doc)
    :Binary(ti, des, doc), audioPath(aPath)
{}
AudioNote::AudioNote(const QString& filePath, const QString& ti, const QString& des, const QString& aPath, Document *doc)
    :Binary(filePath, ti, des, doc), audioPath(aPath)
{}

AudioNoteEditor* AudioNote::createEditor(){
    return new AudioNoteEditor(this);
}

/***
 * VideoNote
 */
VideoNote::VideoNote(const QString& ti, const QString& des, const QString& vPath, Document *doc)
    :Binary(ti, des, doc), videoPath(vPath)
{}
VideoNote::VideoNote(const QString& filePath, const QString& ti, const QString& des, const QString& vPath, Document *doc)
    :Binary(filePath, ti, des, doc), videoPath(vPath)
{}

VideoNoteEditor* VideoNote::createEditor(){
    return new VideoNoteEditor(this);
}


/***
 * ImageNote
 */
ImageNote::ImageNote(const QString& filepath)
    :Binary(filepath)
{}

ImageNote::ImageNote(const QString& filePath, const QString& ti, const QString& des, const QString& iPath)
    :Binary(filePath, ti, des, iPath)
{}

ImageNoteEditor *ImageNote::createEditor()
{
    return new ImageNoteEditor(this);
}

/***
 * Document
 */

Document::Document(const QString &path)
    :Note(path)
{}

Document::Document(const QString &path, const QString &ti)
    :Note(path, ti)
{}

QSet<Note *>::iterator Document::begin(){
    return notes.begin();
}

QSet<Note *>::iterator Document::end(){
    return notes.end();
}

void Document::addNote(const Note* note)
{
    this->notes << note;
}

void Document::removeNote(const Note* note)
{
    this->notes.remove(note);
}

DocumentEditor* Document::createEditor(){
    return new DocumentEditor(this);
}

