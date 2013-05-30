#ifndef TAG_H
#define TAG_H

#include <QObject>
#include <QString>
#include <QSet>

class Note;

class Tag
{
    QString name;
    QSet<Note*> assocs;

public:
    Tag(const QString& n);
    QString getName() { return name; }
    QSet<Note*> getAssocs() { return assocs; }
    void addNote(const Note* n);
};

#endif // TAG_H
