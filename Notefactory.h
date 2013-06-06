#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <QString>
#include <iostream>
#include <QMap>

class Article;
class ImageNote;
class AudioNote;
class VideoNote;
class Document;
class TagManager;
class Note;

enum NoteType {article=1, document, imageNote, videoNote, audioNote, unknownType};

class NoteFactory
{
protected:
    TagManager *tm;
public:
    QString generateID();
    static QMap<NoteType, NoteFactory*>* getFactories();

    NoteFactory();

    Article * buildArticleCopy(const Article& note);
    Document * buildDocumentCopy(const Document& note);
    ImageNote * buildImageNoteCopy(const ImageNote& note);
    AudioNote * buildAudioNoteCopy(const AudioNote& note);
    VideoNote * buildVideoNoteCopy(const VideoNote& note);

    virtual QString generateNewFilePath();
    virtual Note* buildNote(const QString& path) = 0;
    virtual Note* buildNewNote() = 0;
    Note* buildNoteCopy(const Note& n);
    QString getFullFolder();
    virtual QString getFolder() = 0;
    virtual QString getExtension() = 0;

};

#endif // NOTEFACTORY_H
