#ifndef NOTES_H
#define NOTES_H

#include <QSet>
#include "BaseEditor.h"
#include "Editors.h"

class Binary;
class ImageNote;
class VideoNote;
class AudioNote;
class Article;
class Note;
class Document;

class NotesException{
public:
    NotesException(const QString& message);
    QString getInfo() const;
private:
    QString info;
};

class Note{
    QString title;
    QString filePath;
    bool modified;
    bool deleted;

public:
    Note(const QString &path);
    Note(const QString &path, const QString& ti);

    virtual ~Note(){}

    const QString &getTitle() const;
    void setTitle(QString &t);

    const QString &getFilePath() const;
    void setFilePath(const QString &p);

    void setModified(bool b);
    bool isModified() const;

    void setDeleted(bool b);
    bool isDeleted() const;

    virtual Editor *createEditor() = 0;
    virtual const QString & exportNote(ExportStrategy *es, unsigned int level = 0);

};

class Article: public Note {
    QString text;

public:

    Article(const QString& filePath);
    Article::Article(const QString& path, const QString& ti, const QString& te);

    const QString& getText() const;
    void setText(const QString& t);

    ArticleEditor *createEditor();
};

/**
 * @brief The Binary class. Base class for Image, Audio, VideoNote
 */
class Binary: public Note{
    QString description;
    QString mediaPath;
public:
    Binary(const QString& path);
    Binary(const QString& filePath, const QString& ti, const QString& des, const QString& mediaPath);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getMediaPath() const;
    void setMediaPath(const QString &value);
};


class ImageNote: public Binary{
public:
    ImageNote(const QString& filepath);
    ImageNote(const QString& filePath, const QString& ti, const QString& des, const QString& iPath);

    ImageNoteEditor *createEditor();
};


/**
 * @TODO createEditor()
 */
class VideoNote: public Binary{
public:
    VideoNote(const QString& filePath);
    VideoNote(const QString& filePath, const QString& ti, const QString& des, const QString& vPath);
    VideoNoteEditor *createEditor(){}
};

/**
 * @TODO createEditor()
 */
class AudioNote: public Binary{
public:
    AudioNote(const QString& filePath);
    AudioNote(const QString& filePath, const QString& ti, const QString& des, const QString& aPath);
    AudioNoteEditor *createEditor(){}
};


class Document: public Note{
    QSet<Note *> notes;

public:
    Document(const QString& path);
    Document(const QString& path, const QString& ti);

    QSet<Note *>::iterator begin();
    QSet<Note *>::iterator end();

    void addNote(const Note *note);
    void removeNote(const Note *note);

    const QSet<Note> &getNotes() const;
    void setNotes(const QSet<Note> &value);

    DocumentEditor *createEditor(){}
};


#endif

