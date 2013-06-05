#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <QString>
#include <iostream>
#include <QMap>

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

    virtual QString generateNewFilePath();
    virtual Note* buildNote(const QString& path) = 0;
    virtual Note* buildNewNote() = 0;
//    virtual Note* buildNoteCopy(const Note& note) = 0;
    QString getFullFolder();
    virtual QString getFolder() = 0;
    virtual QString getExtension() = 0;

};

#endif // NOTEFACTORY_H
