#ifndef NOTE_H
#define NOTE_H

#include <QSet>
#include <QString>

#include "Editor.h"

class ExportStrategy;

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
    virtual QString exportNote(const ExportStrategy *es, unsigned int level = 0) = 0;

};



#endif

