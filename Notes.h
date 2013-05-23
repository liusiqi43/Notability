#ifndef NOTES_H
#define NOTES_H

#include "BaseEditor.h"
#include "Editors.h"

class Binary;
class ImageNote;
class VideoNote;
class AudioNote;
class Article;
class Note;
class Document;

QTextStream& operator<<(QTextStream& f, const Article& a);
QTextStream& operator<<(QTextStream& f, const Document& d);
QTextStream& operator<<(QTextStream& f, const ImageNote& i);

class NotesException{
public:
    NotesException(const QString& message);
    QString getInfo() const;
private:
    QString info;
};

class Note{
    friend class NotesManager;

    QString title;
    QString filePath;
    bool modified;
    // TODO
    Document *document;

    /**
     * @brief getCategory, implemented in subclasses
     * @return currentWorkSpace+"/IMG/"+"IMG" for images, "/ART/ART" for articles, "/VID/VID" for videos, "/AUD/AUD" for audios.
     */
    virtual QString getCategory() = 0;

    virtual QString getExtension() = 0;

public:
    Note(QString ti, Document *doc = 0);
    Note(QString ti, QString path, Document *doc = 0);

    /**
     * @brief getFilePath template method, delegate getCategory to subclasses
     * @return FilePath based on noteType and current workspace
     */
    const QString generateFilePath();

    virtual ~Note(){}
    const QString &getTitle() const;
    const QString &getFilePath() const;
    void setFilePath(const QString &p);

    Document *getDocument() const;

    void setTitle(QString &t);

    void setModified(bool b);
    bool isModified() const;

    virtual void save() = 0;
    virtual Editor *createEditor() = 0;
};

class Article: public Note {
    friend class NotesManager;
    QString text;

    QString getCategory();
    QString getExtension();

public:
    Article(const QString& ti, const QString& te, Document *doc = 0);
    Article(const QString& filePath, const QString& ti, const QString& te, Document *doc = 0);
    const QString& getText() const;
    void setText(const QString& t);

    void save();
    ArticleEditor *createEditor();
};

/**
 * @brief The Binary class. Base class for Image, Audio, VideoNote
 */
class Binary: public Note{
    friend class NotesManager;
    QString description;
public:
    Binary(const QString& ti, const QString& des, Document *doc = 0);
    Binary(const QString& filePath, const QString& ti, const QString& des, Document *doc = 0);

    QString getDescription() const;
    void setDescription(const QString &value);
};


class ImageNote: public Binary{
    friend class NotesManager;
    QString imgPath;

    QString getCategory();
    QString getExtension();
public:
    ImageNote(const QString& ti, const QString& des, const QString& iPath, Document *doc = 0);
    ImageNote(const QString& filePath, const QString& ti, const QString& des, const QString& iPath, Document *doc = 0);

    QString getImgPath() const;
    void setImgPath(const QString &value);
    void save();
    ImageNoteEditor *createEditor();
};


class VideoNote: public Binary{
    friend class NotesManager;
    QString videoPath;
    QString getCategory();
    QString getExtension();
public:
    VideoNote(const QString& ti, const QString& des, const QString& vPath, Document *doc = 0);
    VideoNote(const QString& filePath, const QString& ti, const QString& des, const QString& vPath, Document *doc = 0);

    QString getVideoPath() const;
    void setVideoPath(const QString &value);
//    void save();
};


class AudioNote: public Binary{
    friend class NotesManager;
    QString audioPath;
    QString getCategory();
    QString getExtension();
public:
    AudioNote(const QString& ti, const QString& des, const QString& aPath, Document *doc = 0);
    AudioNote(const QString& filePath, const QString& ti, const QString& des, const QString& aPath, Document *doc = 0);

    QString getAudioPath() const;
    void setAudioPath(const QString &value);
//    void save();
};




#endif

