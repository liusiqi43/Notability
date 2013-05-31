#ifndef AUDIONOTE_H
#define AUDIONOTE_H


#include "Binary.h"
#include "AudioNoteEditor.h"


class AudioNote: public Binary{
public:
    AudioNote(const QString& filePath);
    AudioNote(const QString& filePath, const QString& ti, const QString& des, const QString& aPath);
    AudioNoteEditor *createEditor(){return new AudioNoteEditor(this);}
    QString exportNote(const ExportStrategy *es, unsigned int level = 0);
};

#endif // AUDIONOTE_H
