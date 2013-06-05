
#include "DocumentFactory.h"
#include <QFile>
#include <QTextStream>
#include <exception>
#include "NotesManager.h"
#include "TagManager.h"
#include "Trash.h"

/***
 * Document
 */

Document* DocumentFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
        return 0;
    }
    QTextStream flux(&fichier);

    QString fpath = flux.readLine();
    QString title=flux.readLine();
    Document *d = new Document(fpath, title);

    QString tags = flux.readLine();

    QStringList tagList = QStringList();
    if(!tags.isEmpty())
        tagList = tags.split("|||");
    qDebug()<<"Factory: getting taglist: " << tagList;

    for(QStringList::iterator it = tagList.begin(); it!=tagList.end(); ++it){
        Tag* t = this->tm->getTag(*it);
        // double binding method
        tm->addTagToNote(t, d);
    }

    QString isDeleted = flux.readLine();

    NotesManager *nm = &NotesManager::getInstance();

    QString notePath = "";

    while(!notePath.isNull()) {
         notePath = flux.readLine();
         qDebug()<<"getting note path from Doc" << notePath;
         QFile noteFile(notePath);
         if(noteFile.open(QIODevice::ReadOnly | QIODevice::Text))
            d->addNote(&nm->getNote(notePath));
         else
             break;
    }

    fichier.close();

    // We do this at the end so that all documents are properly loaded.
    if(isDeleted == "isDeleted"){
        // Trash will take care of all unbinding staff
        Trash::getInstance()->recycle(d);
    }
    else
        d->setDeleted(false);

    return d;
}


Document* DocumentFactory::buildNewNote()
{
    return new Document(generateNewFilePath());
}


Document* DocumentFactory::buildNoteCopy(const Document &note)
{
    Document *d = new Document(generateNewFilePath(), note.getTitle());
    NotesManager *nm = &NotesManager::getInstance();

    for(QList<Note*>::const_iterator it = note.begin(); it != note.end(); it++){
        // TODO test si ca va marcher....il est cense de generer une nouvelle copie de Note avec filePath differente
        Note * nCopy = &nm->getNoteClone((*it)->getFilePath());
        d->addNote(nCopy);
    }
    return d;
}


QString DocumentFactory::getFolder()
{
    return "DOC/";
}


QString DocumentFactory::getExtension()
{
    return ".doc";
}
