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
QMap<NoteType, NoteFactory*> NoteFactory::factories;

NoteFactory::NoteFactory()
{}

QMap<NoteType, NoteFactory*> NoteFactory::getFactories()
{
    factories[article] = new ArticleFactory();
    factories[document] = new DocumentFactory();
    factories[imageNote] = new ImageNoteFactory();
    factories[videoNote] = new VideoNoteFactory();
    factories[audioNote] = new AudioNoteFactory();
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

