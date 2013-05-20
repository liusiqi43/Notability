#ifndef NOTES_H
#define NOTES_H

#include <QString>
#include <QTextStream>
#include "AppManager.h"

class Article;
class Note;
class Document;
class NotesManager;


QTextStream& operator<<(QTextStream& f, const Article& a);
QTextStream& operator<<(QTextStream& f, const Document& d);

class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
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
    const QString &getTitle() const {return title;}
    const QString &getFilePath() const {return filePath;}
    void setFilePath(const QString &p) {filePath = p; modified=true;}

    Document *getDocument() const {return document;}

    void setTitle(QString &t) {title = t; modified = true;}

    void setModified(bool b) {modified = b;}
    bool isModified() const {return modified;}

    virtual void save() = 0;
    virtual QString toHTML() = 0;
};

class Article: public Note {
    friend class NotesManager;
    QString text;

    QString getCategory();
    QString getExtension();

public:
    Article(const QString& ti, const QString& te, Document *doc = 0);
    Article(const QString& filePath, const QString& ti, const QString& te, Document *doc = 0);
    const QString& getText() const { return text; }
    void setText(const QString& t);

    QString toHTML();
    void save();
};

/**
 * @brief The Binary class. Base class for Image, Audio, VideoNote
 */
class Binary: public Note{
    friend class NotesManager;
    QString description;
public:
    Binary(const QString& ti, const QString& des, Document *doc = 0)
        :Note(ti, doc), description(des)
    {}
    Binary(const QString& filePath, const QString& ti, const QString& des, Document *doc = 0)
        :Note(ti, filePath, doc), description(des)
    {}
    QString getDescription() const;
    void setDescription(const QString &value);
};
class ImageNote: public Binary{
    friend class NotesManager;
    QString imgPath;
    QString getCategory();
    QString getExtension();
public:
    ImageNote(const QString& ti, const QString& des, const QString& iPath, Document *doc = 0)
        :Binary(ti, des, doc), imgPath(iPath)
    {}
    ImageNote(const QString& filePath, const QString& ti, const QString& des, const QString& iPath, Document *doc = 0)
        :Binary(filePath, ti, des, doc), imgPath(iPath)
    {}
    QString getImgPath() const;
    void setImgPath(const QString &value);
    QString toHTML();
    void save();
};
class VideoNote: public Binary{
    friend class NotesManager;
    QString videoPath;
    QString getCategory();
    QString getExtension();
public:
    VideoNote(const QString& ti, const QString& des, const QString& vPath, Document *doc = 0)
        :Binary(ti, des, doc), videoPath(vPath)
    {}
    VideoNote(const QString& filePath, const QString& ti, const QString& des, const QString& vPath, Document *doc = 0)
        :Binary(filePath, ti, des, doc), videoPath(vPath)
    {}
    QString getVideoPath() const;
    void setVideoPath(const QString &value);
    QString toHTML();
    void save();
};
class AudioNote: public Binary{
    friend class NotesManager;
    QString audioPath;
    QString getCategory();
    QString getExtension();
public:
    AudioNote(const QString& ti, const QString& des, const QString& aPath, Document *doc = 0)
        :Binary(ti, des, doc), audioPath(aPath)
    {}
    AudioNote(const QString& filePath, const QString& ti, const QString& des, const QString& aPath, Document *doc = 0)
        :Binary(filePath, ti, des, doc), audioPath(aPath)
    {}
    QString getAudioPath() const;
    void setAudioPath(const QString &value);
    QString toHTML();
    void save();
};




#endif

