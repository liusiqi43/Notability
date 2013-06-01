#include "ArticleFactory.h"
#include "Article.h"
#include "Note.h"
#include <QFile>
#include <QTextStream>

/***
 * ArticleFactory
 */

Article* ArticleFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;
    QTextStream flux(&fichier);

    QString fpath = flux.readLine();
    QString title=flux.readLine();
    QString text;
    QString temp("");
    while(!temp.isNull()){
        temp=flux.readLine();
        text+=temp+"\n";
    }
    fichier.close();
    qDebug()<<fpath;
    Article *a=new Article(fpath,title,text);
    return a;
}


Article *ArticleFactory::buildNewNote()
{
    return new Article(generateNewFilePath());
}


Article* ArticleFactory::buildNoteCopy(const Article &note)
{
    return new Article(generateNewFilePath(), note.getTitle(), note.getText());
}


QString ArticleFactory::getFolder()
{
    return "ART/";
}


QString ArticleFactory::getExtension()
{
    return ".art";
}

