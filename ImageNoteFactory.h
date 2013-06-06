#ifndef IMAGENOTEFACTORY_H
#define IMAGENOTEFACTORY_H

#include "NoteFactory.h"
#include "ImageNote.h"

class ImageNoteFactory : public NoteFactory
{
public:
    ImageNote* buildNewNote();
    ImageNote* buildNote(const QString &path);
//    ImageNote* buildNoteCopy(const Note &note);
    QString getFolder();
    QString getExtension();
};


#endif // IMAGENOTEFACTORY_H
