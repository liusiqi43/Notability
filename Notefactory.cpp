#include "NoteFactory.h"
#include "ImageNoteFactory.h"
#include "AudioNoteFactory.h"
#include "VideoNoteFactory.h"
#include "ArticleFactory.h"
#include "DocumentFactory.h"
#include "TagManager.h"
#include "NotesManager.h"

#include <QMap>
#include <QApplication>
#include <QSettings>
#include <QDateTime>
#include <QUuid>

/***
 * NoteFactory
 */

NoteFactory::NoteFactory()
{
    tm = &TagManager::getInstance();
}

Article *NoteFactory::buildArticleCopy(const Article &note)
{
    QString fpath = generateNewFilePath();
    QString title=note.getTitle();
    QString text = note.getText();
    Article *a=new Article(fpath,title,text);

    a->setTags(note.getTags());
    a->setDeleted(note.isDeleted());

    return a;
}

Document *NoteFactory::buildDocumentCopy(const Document &note)
{
    Document *d = new Document(generateNewFilePath(), note.getTitle());
    NotesManager *nm = &NotesManager::getInstance();

    for(QList<Note*>::const_iterator it = note.begin(); it != note.end(); it++){
        Note * nCopy = &nm->getNoteClone((**it));
        d->addNote(nCopy);
    }
    return d;
}

ImageNote *NoteFactory::buildImageNoteCopy(const ImageNote &note)
{
    ImageNote * a = new ImageNote(generateNewFilePath(), note.getTitle(), note.getDescription(), note.getMediaPath());

    a->setTags(note.getTags());
    a->setDeleted(note.isDeleted());

    return a;
}

AudioNote *NoteFactory::buildAudioNoteCopy(const AudioNote &note)
{
    AudioNote * a = new AudioNote(generateNewFilePath(), note.getTitle(), note.getDescription(), note.getMediaPath());

    a->setTags(note.getTags());
    a->setDeleted(note.isDeleted());

    return a;
}

VideoNote *NoteFactory::buildVideoNoteCopy(const VideoNote &note)
{
    VideoNote * a = new VideoNote(generateNewFilePath(), note.getTitle(), note.getDescription(), note.getMediaPath());

    a->setTags(note.getTags());
    a->setDeleted(note.isDeleted());

    return a;
}

QMap<NoteType, NoteFactory *> *NoteFactory::getFactories()
{
    QMap<NoteType, NoteFactory *> *factories = new QMap<NoteType, NoteFactory*>();
    factories->insert(article,new ArticleFactory());
    factories->insert(document,new DocumentFactory());
    factories->insert(imageNote,new ImageNoteFactory());
    factories->insert(videoNote,new VideoNoteFactory());
    factories->insert(audioNote,new AudioNoteFactory());
    return factories;
}

QString NoteFactory::generateNewFilePath()
{
    QString path = this->getFullFolder()+generateID()+this->getExtension();
    qDebug()<<path;
    return path;
}

Note *NoteFactory::buildNoteCopy(const Note &note)
{
    switch(note.type){
    case document:
        return buildDocumentCopy(dynamic_cast<const Document&>(note));

    case article:
        return buildArticleCopy(dynamic_cast<const Article&>(note));

    case imageNote:
        return buildImageNoteCopy(dynamic_cast<const ImageNote&>(note));

    case audioNote:
        return buildAudioNoteCopy(dynamic_cast<const AudioNote&>(note));

    case videoNote:
        return buildVideoNoteCopy(dynamic_cast<const VideoNote&>(note));

    default:
        throw NotesException("Unknown note type when copy note.");
    }
}

QString NoteFactory::getFullFolder()
{
    QSettings settings;
    QString dir;
    if(!settings.contains("workspace"))
        settings.setValue("workspace", qApp->applicationDirPath());
    dir = settings.value("workspace").toString()+"/"+this->getFolder();
    return dir;
}

QString NoteFactory::generateID(){
    QSettings settings;
    qint64 thisone;
    if(!settings.value("nextUUid").isNull()){
        thisone = settings.value("nextUUid").toInt();
        settings.setValue("nextUUid", settings.value("nextUUid").toInt()+1);
    } else {
        thisone = QDateTime::currentDateTime().toMSecsSinceEpoch();
        settings.setValue("nextUUid", thisone+1);
    }
    return QString::number(thisone);
}

