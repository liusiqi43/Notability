#ifndef IMAGENOTE_H
#define IMAGENOTE_H

#include "Binary.h"
#include "ImageNoteEditor.h"

class ImageNote: public Binary{
public:
    ImageNote(const QString& filepath);
    ImageNote(const QString& filePath, const QString& ti, const QString& des, const QString& iPath);

    ImageNoteEditor *createEditor();
    QString exportNote(const ExportStrategy *es, unsigned int level = 0);
};


#endif // IMAGENOTE_H
