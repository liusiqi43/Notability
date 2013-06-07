#include "ImageNoteFactory.h"
#include <QFile>
#include <QTextStream>
#include "Article.h"
#include "Trash.h"
#include "TagManager.h"

/***
 * ImageNoteFactory
 */

ImageNote* ImageNoteFactory::buildNote(const QString &path)
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
    QString isDeleted = flux.readLine();

    QString des =flux.readLine();
    QString ipath = flux.readLine();

    fichier.close(); qDebug()<<fpath;

    ImageNote* a=new ImageNote(fpath,title,des,ipath);

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


ImageNote* ImageNoteFactory::buildNewNote()
{
    return new ImageNote(generateNewFilePath());
}


QString ImageNoteFactory::getFolder()
{
    return "IMG/";
}


QString ImageNoteFactory::getExtension()
{
    return ".img";
}


