#include "VideoNoteFactory.h"
#include "Trash.h"
#include <QFile>
#include <QTextStream>
#include "TagManager.h"

/***
 * VideoNoteFactory
 */

VideoNote* VideoNoteFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString fpath = flux.readLine();
    QString title=flux.readLine();

    QString tags = flux.readLine();
    QStringList tagList = QStringList();
    if(!tags.isEmpty())
        tagList = tags.split("|||");
    QString isDeleted = flux.readLine();

    QString des =flux.readLine();
    QString vpath = flux.readLine();

    fichier.close();

    VideoNote* a=new VideoNote(fpath,title,des,vpath);

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


VideoNote* VideoNoteFactory::buildNewNote()
{
    return new VideoNote(generateNewFilePath());
}


QString VideoNoteFactory::getFolder()
{
    return "VID/";
}


QString VideoNoteFactory::getExtension()
{
    return ".vid";
}
