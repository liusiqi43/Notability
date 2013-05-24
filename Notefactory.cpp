#include "NoteFactory.h"
#include "AppManager.h"
#include "Notes.h"
#include <QMap>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QSet>
#include "NotesManager.h"

/***
 * NoteFactory
 */

NoteFactory::NoteFactory()
{}

static QMap<NoteType, NoteFactory*> NoteFactory::getFactories()
{
    factories[article] = new ArticleFactory();
    factories[document] = new DocumentFactory();
    factories[imageNote] = new ImageNoteFactory();
    factories[videoNote] = new VideoNoteFactory();
    factories[audioNote] = new AudioNoteFactory();
    return factories;
}

const QString &NoteFactory::generateNewFilePath()
{
    return this->getFolder()+generateID()+this->getExtension();
}

const QString& NoteFactory::generateID(){
    QDateTime t = QDateTime::currentDateTime();
    return t.toString("yyyyMMddzzzssmmhh");
}

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

    Article* a=new Article(path,title,text);
    return *a;
}


Article *ArticleFactory::buildNewNote()
{
    return new Article(generateNewFilePath());
}


Article* ArticleFactory::buildNoteCopy(const Article &note)
{
    return new Article(generateNewFilePath(), note.getTitle(), note.getText());
}


const QString& ArticleFactory::getFolder()
{
    return "ART/";
}


const QString& ArticleFactory::getExtension()
{
    return ".art";
}


/***
 * ImageNoteFactory
 */

ImageNote* ImageNoteFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString title=flux.readLine();
    QString des =flux.readLine();
    QString ipath = flux.readLine();

    fichier.close();

    Article* a=new ImageNote(path,title,des,ipath);
    return a;
}


ImageNote* ImageNoteFactory::buildNewNote()
{
    return new ImageNote(generateNewFilePath());
}


ImageNote* ImageNoteFactory::buildNoteCopy(const ImageNote &note)
{
    return new ImageNote(generateNewFilePath(), note.getTitle(), note.getDescription(), note.getMediaPath());
}


const QString& ImageNoteFactory::getFolder()
{
    return "IMG/";
}


const QString& ImageNoteFactory::getExtension()
{
    return ".img";
}



/***
 * AudioNoteFactory
 */

AudioNote* AudioNoteFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString title=flux.readLine();
    QString des =flux.readLine();
    QString apath = flux.readLine();

    fichier.close();

    Article* a=new AudioNote(path,title,des,apath);
    return a;
}


AudioNote* AudioNoteFactory::buildNewNote()
{
    return new AudioNote(generateNewFilePath());
}


AudioNote* AudioNoteFactory::buildNoteCopy(const AudioNote &note)
{
    return new AudioNote(generateNewFilePath(), note.getTitle(), note.getDescription(), note.getMediaPath());
}


const QString& AudioNoteFactory::getFolder()
{
    return "AUD/";
}


const QString& AudioNoteFactory::getExtension()
{
    return ".aud";
}


/***
 * VideoNoteFactory
 */

VideoNote* VideoNoteFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString title=flux.readLine();
    QString des =flux.readLine();
    QString vpath = flux.readLine();

    fichier.close();

    Article* a=new VideoNote(path,title,des,vpath);
    return a;
}


VideoNote* VideoNoteFactory::buildNewNote()
{
    return new VideoNote(generateNewFilePath());
}


VideoNote* VideoNoteFactory::buildNoteCopy(const VideoNote &note)
{
    return new VideoNote(generateNewFilePath(), note.getTitle(), note.getDescription(), note.getMediaPath());
}


const QString& VideoNoteFactory::getFolder()
{
    return "VID/";
}


const QString& VideoNoteFactory::getExtension()
{
    return ".vid";
}

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

    NotesManager *nm = NotesManager::getInstance();

    QString notePath = "";

    while(!notePath.isNull()) {
         notePath = flux.readLine();
        if(!notePath.isNull())
            d->addNote(*(nm->getNote(notePath)));
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
    QSet<Note> set = note.getNotes();
    Document *d = new Document(generateNewFilePath(), note.getTitle());
    NotesManager *nm = NotesManager::getInstance();

    for(QSet<Note*>::iterator it = note.begin(); it != note.end(); it++){
        // TODO test si ca va marcher....il est cense de generer une nouvelle copie de Note avec filePath differente
        Note * nCopy = nm->getNoteClone(n.getFilePath());
        d->addNote(nCopy);
    }
    return d;
}


const QString& DocumentFactory::getFolder()
{
    return "DOC/";
}


const QString& DocumentFactory::getExtension()
{
    return ".doc";
}
