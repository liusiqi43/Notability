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


    QSet<Note*> getAssocs() { return assocs; }
    void addNote(Note *n);
    void removeNote(const Note* n);
    void reset() {assocs.clear();}
    QString getName() const;
    void setName(const QString &value);
};

#endif // TAG_H
