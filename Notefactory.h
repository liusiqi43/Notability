#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <QString>
#include <iostream>
#include <QMap>
#include "AppManager.h"

class Note;
class VideoNoteFactory;
class AudioNoteFactory;
class DocumentFactory;
class ImageNoteFactory;
class ArticleFactory;

enum NoteType {article=1, document, imageNote, videoNote, audioNote, unknownType};

class NoteFactory
{
    static QMap<NoteType, NoteFactory*> factories;
public:
    const QString& generateID();
    static QMap<NoteType, NoteFactory*> getFactories();

    NoteFactory();

    virtual const QString& generateNewFilePath();
    virtual Note* buildNote(const QString& path) = 0;
    virtual Note* buildNewNote() = 0;
    virtual Note* buildNoteCopy(const Note& note) = 0;
    virtual const QString& getFolder() = 0;
    virtual const QString& getExtension() = 0;

};

class ArticleFactory : public NoteFactory
{
public:
    Article* buildNewNote();
    Article* buildNote(const QString &path);
    Article* buildNoteCopy(const Article &note);
    const QString& getFolder();
    const QString& getExtension();
};


class ImageNoteFactory : public NoteFactory
{
public:
    ImageNote* buildNewNote();
    ImageNote* buildNote(const QString &path);
    ImageNote* buildNoteCopy(const ImageNote &note);
    const QString& getFolder();
    const QString& getExtension();
};

class AudioNoteFactory : public NoteFactory
{
public:
    AudioNote* buildNewNote();
    AudioNote* buildNote(const QString &path);
    AudioNote* buildNoteCopy(const AudioNote &note);
    const QString& getFolder();
    const QString& getExtension();
};

class VideoNoteFactory : public NoteFactory
{
public:
    VideoNote* buildNewNote();
    VideoNote* buildNote(const QString &path);
    VideoNote* buildNoteCopy(const VideoNote &note);
    const QString& getFolder();
    const QString& getExtension();
};

class DocumentFactory : public NoteFactory
{
public:
    Document* buildNewNote();
    Document* buildNote(const QString &path);
    Document* buildNoteCopy(const Document &note);
    const QString& getFolder();
    const QString& getExtension();
};

#endif // NOTEFACTORY_H
