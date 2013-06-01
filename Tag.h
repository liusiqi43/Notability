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

    // Interdit l'instanciation sans passer par TagManager.
    Tag(const QString& n);

    Tag(const Tag& other);
    const Tag& operator=(const Tag other);

public:
    friend class TagManager;

    QSet<Note*> getAssocs() { return assocs; }
    void addNote(Note *n);
    void removeNote(const Note* n);
    void reset() {assocs.clear();}
    QString getName() const;
    void setName(const QString &value);

};

#endif // TAG_H
