#include "ArticleFactory.h"
#include "Article.h"
#include "Note.h"
#include "Trash.h"
#include <QFile>
#include <QTextStream>
#include "TagManager.h"

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

    QString tags = flux.readLine();
    QStringList tagList = QStringList();
    if(!tags.isEmpty())
        tagList = tags.split("|||");
    qDebug()<<"Factory: getting taglist: " << tagList;
    QString isDeleted = flux.readLine();

    QString text;
    QString temp("");
    while(!temp.isNull()){
        temp=flux.readLine();
        text+=temp+"\n";
    }
    fichier.close();
    qDebug()<<fpath;
    Article *a=new Article(fpath,title,text);

    for(QStringList::iterator it = tagList.begin(); it!=tagList.end(); ++it){
        Tag* t = this->tm->getTag(*it);
        // double binding method
        tm->addTagToNote(t, a);
    }

    // We do this at the end so that all documents are properly loaded.
    if(isDeleted == "isDeleted"){
        // Trash will take care of all unbinding staff
        Trash::getInstance()->recycle(a);
    }
    a->setModified(false);
    return a;
}


Article *ArticleFactory::buildNewNote()
{
    return new Article(generateNewFilePath());
}


QString ArticleFactory::getFolder()
{
    return "ART/";
}


QString ArticleFactory::getExtension()
{
    return ".art";
}

