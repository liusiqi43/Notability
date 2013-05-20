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

const QString & Note::getTitle() const {return title;}
const QString & Note::getFilePath() const {return filePath;}
void Note::setFilePath(const QString &p) {filePath = p; modified=true;}

Document * Note::getDocument() const {return document;}

void Note::setTitle(QString &t) {title = t; modified = true;}

void Note::setModified(bool b) {modified = b;}
bool Note::isModified() const {return modified;}

const QString Note::generateFilePath() {
    return this->getCategory()+AppManager::getInstance().generateID()+this->getExtension();
}

Note::Note(QString ti, Document *doc):title(ti), document(doc){}

Note::Note(QString ti, QString path, Document *doc):title(ti), filePath(path), document(doc){}

/***
 *  Article
 */

/**
 * @brief Article::Article, create new Article
 * @param ti title
 * @param te text
 * @param doc container document
 */
Article::Article(const QString& ti, const QString& te, Document *doc):
    Note(ti, doc),text(te) {
    this->setFilePath(this->generateFilePath());
    qDebug()<<this->getFilePath();
}

Article::Article(const QString &filePath, const QString &ti, const QString &te, Document *doc)
    :Note(ti, filePath, doc), text(te){}

QTextStream& operator<<(QTextStream& f, const Article& a){
    f<<a.getTitle()<<"\n";
    f<<a.getText()<<"\n";
    return f;
}

const QString& Article::getText() const { return text; }

void Article::setText(const QString& t) {
    setModified(true);
    text=t;
}

void Article::save(){
    NotesManager::getInstance().saveArticle(*this);
}

ArticleEditor *Article::createEditor()
{
    return new ArticleEditor(this);
}

QString Article::getCategory(){
    return AppManager::getWorkSpace()+QString("/ART/ART");
}

QString Article::getExtension(){
    return QString(".txt");
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

QString VideoNote::getVideoPath() const
{
    return videoPath;
}

void VideoNote::setVideoPath(const QString &value)
{
    setModified(true);
    videoPath = value;
}

QString VideoNote::getCategory()
{
    return AppManager::getWorkSpace()+QString("/VID/VID");
}

QString VideoNote::getExtension(){
    return QString(".vid");
}

/***
 * ImageNote
 */
ImageNote::ImageNote(const QString& ti, const QString& des, const QString& iPath, Document *doc)
    :Binary(ti, des, doc), imgPath(iPath)
{
    this->setFilePath(this->generateFilePath());
    qDebug()<<this->getFilePath();
}
ImageNote::ImageNote(const QString& filePath, const QString& ti, const QString& des, const QString& iPath, Document *doc)
    :Binary(filePath, ti, des, doc), imgPath(iPath)
{}

QString ImageNote::getImgPath() const
{
    return imgPath;
}
void ImageNote::setImgPath(const QString &value)
{
    setModified(true);
    imgPath = value;
}

void ImageNote::save()
{
    NotesManager::getInstance().saveImageNote(*this);
}

ImageNoteEditor *ImageNote::createEditor()
{
    return new ImageNoteEditor(this);
}

QString ImageNote::getCategory()
{
    return AppManager::getWorkSpace()+QString("/IMG/IMG");
}

QString ImageNote::getExtension(){
    return QString(".img");
}

QTextStream& operator<<(QTextStream& f, const ImageNote& i){
    f<<i.getTitle()<<"\n";
    f<<i.getImgPath()<<"\n";
    f<<i.getDescription()<<"\n";
    return f;
}


/***
 * Binary
 */

Binary::Binary(const QString& ti, const QString& des, Document *doc)
    :Note(ti, doc), description(des)
{}
Binary::Binary(const QString& filePath, const QString& ti, const QString& des, Document *doc)
    :Note(ti, filePath, doc), description(des)
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

/***
 * AudioNote
 */
AudioNote::AudioNote(const QString& ti, const QString& des, const QString& aPath, Document *doc)
    :Binary(ti, des, doc), audioPath(aPath)
{}
AudioNote::AudioNote(const QString& filePath, const QString& ti, const QString& des, const QString& aPath, Document *doc)
    :Binary(filePath, ti, des, doc), audioPath(aPath)
{}

QString AudioNote::getAudioPath() const
{
    return audioPath;
}

void AudioNote::setAudioPath(const QString &value)
{
    setModified(true);
    audioPath = value;
}

QString AudioNote::getCategory()
{
    return AppManager::getWorkSpace()+QString("/AUD/AUD");
}

QString AudioNote::getExtension(){
    return QString(".aud");
}
