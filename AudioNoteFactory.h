#ifndef AUDIONOTEFACTORY_H
#define AUDIONOTEFACTORY_H

#include "NoteFactory.h"
#include "AudioNote.h"

class AudioNoteFactory : public NoteFactory
{
public:
    AudioNote* buildNewNote();
    AudioNote* buildNote(const QString &path);
    AudioNote* buildNoteCopy(const AudioNote &note);
    QString getFolder();
    QString getExtension();
};
#endif // AUDIONOTEFACTORY_H
