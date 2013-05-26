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
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString title=flux.readLine();
    QString text=flux.readLine();
    fichier.close();

    Article *a=new Article(path,title,text);
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

