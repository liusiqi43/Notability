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

/**
 * @brief Article::Article
 * @param a
 */
Article::Article(const Article& a):
    Note(a.getTitle(), a.getFilePath(), a.getDocument()), text(a.getText()){}

Article::Article(const QString &filePath, const QString &ti, const QString &te, Document *doc)
    :Note(ti, filePath, doc), text(te){}

Article& Article::operator=(const Article& a){
    QString old = this->getFilePath();
    *this = a;
    this->setFilePath(old);
    this->setModified(true);
    return *this;
}

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
            this->getTitle()+"</title></head><body><p>"+
            this->getText()+"</p></body></html>";
}

QString Article::getCategory(){
    return AppManager::getWorkSpace()+QString("/ART/ART");
}

QString Article::getExtension(){
    return QString(".txt");
}
