#ifndef AUDIONOTE_H
#define AUDIONOTE_H


#include "Binary.h"
#include "AudioNoteEditor.h"

/**
 * @TODO createEditor()
 */
class AudioNote: public Binary{
public:
    AudioNote(const QString& filePath);
    AudioNote(const QString& filePath, const QString& ti, const QString& des, const QString& aPath);
    AudioNoteEditor *createEditor(){}
    QString exportNote(const ExportStrategy *es, unsigned int level = 0);
};

#endif // AUDIONOTE_H
