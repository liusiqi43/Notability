
#include "DocumentFactory.h"
#include <QFile>
#include <QTextStream>
#include "NotesManager.h"

/***
 * Document
 */

Document* DocumentFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString title=flux.readLine();
    Document *d = new Document(path, title);

    NotesManager *nm = &NotesManager::getInstance();

    QString notePath = "";

    while(!notePath.isNull()) {
         notePath = flux.readLine();
        if(!notePath.isNull())
            d->addNote(&nm->getNote(notePath));
    }

    fichier.close();
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

    for(QSet<Note*>::const_iterator it = note.begin(); it != note.end(); it++){
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
