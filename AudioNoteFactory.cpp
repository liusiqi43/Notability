#include "AudioNoteFactory.h"
#include "Trash.h"
#include <QFile>
#include <QTextStream>
#include "TagManager.h"

/***
 * AudioNoteFactory
 */

AudioNote* AudioNoteFactory::buildNote(const QString &path)
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
    QString apath = flux.readLine();

    fichier.close();

    AudioNote* a=new AudioNote(fpath,title,des,apath);

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

    return a;
}


AudioNote* AudioNoteFactory::buildNewNote()
{
    return new AudioNote(generateNewFilePath());
}


QString AudioNoteFactory::getFolder()
{
    return "AUD/";
}


QString AudioNoteFactory::getExtension()
{
    return ".aud";
}
