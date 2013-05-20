#include "Notes.h"
#include "Document.h"
#include "NotesManager.h"
#include <fstream>
#include <QFile>
#include <QDebug>

/***
 *  Note
 */

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

void Article::setText(const QString& t) {
    setModified(true);
    text=t;
}

void Article::save(){
    NotesManager::getInstance().saveArticle(*this);
}

QString Article::toHTML(){
    return "<html><head><meta charset=\"UTF-8\"><title>"+
            this->getTitle()+"</title></head><body>"+
            "<h1>"+this->getTitle()+"</h1>"+
            this->getText()+"</body></html>";
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
QString VideoNote::getVideoPath() const
{
    return videoPath;
}
void VideoNote::setVideoPath(const QString &value)
{
    videoPath = value;
}
/***
 * ImageNote
 */
QString ImageNote::getImgPath() const
{
    return imgPath;
}
void ImageNote::setImgPath(const QString &value)
{
    imgPath = value;
}
/***
 * Binary
 */
QString Binary::getDescription() const
{
    return description;
}
void Binary::setDescription(const QString &value)
{
    description = value;
}
/***
 * AudioNote
 */
QString AudioNote::getAudioPath() const
{
    return audioPath;
}
void AudioNote::setAudioPath(const QString &value)
{
    audioPath = value;
}
