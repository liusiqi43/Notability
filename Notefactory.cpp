#include "NoteFactory.h"
#include "ImageNoteFactory.h"
#include "AudioNoteFactory.h"
#include "VideoNoteFactory.h"
#include "ArticleFactory.h"
#include "DocumentFactory.h"

#include <QMap>
#include <QDateTime>

/***
 * NoteFactory
 */

NoteFactory::NoteFactory()
{}

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
    return this->getFolder()+generateID()+this->getExtension();
}

QString NoteFactory::generateID(){
    QDateTime t = QDateTime::currentDateTime();
    return t.toString("yyyyMMddzzzssmmhh");
}

