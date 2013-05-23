#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

enum NoteType
{
    Article, ImageNote, RecordNote, VideoNote
};

class NoteFactory
{
public:
    NoteFactory();

    Note * getNewNote(NoteType type);
    Note * getNote(const QString& filePath);
    const QString& generateNewFilePath();
};

#endif // NOTEFACTORY_H
