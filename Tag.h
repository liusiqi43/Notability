#ifndef TAG_H
#define TAG_H

#include <QObject>
#include <QString>
#include <QSet>
#include "TagManager.h"

class Note;

class Tag
{
    QString name;
    QSet<Note*> assocs;

public:
    Tag(const Tag& other);
    Tag(const QString& n);
    const Tag& operator=(const Tag other);

    QSet<Note*>& getAssocs() { return assocs; }
    void addNote(Note *n);
    void removeNote(Note* n);
    void reset() {assocs.clear();}
    QString getName() const;
    void setName(const QString &value);

};

#endif // TAG_H
