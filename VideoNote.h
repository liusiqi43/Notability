#ifndef VIDEONOTE_H
#define VIDEONOTE_H

#include "Binary.h"
#include "VideoNoteEditor.h"

/**
 * @TODO createEditor()
 */
class VideoNote: public Binary{
public:
    VideoNote(const QString& filePath);
    VideoNote(const QString& filePath, const QString& ti, const QString& des, const QString& vPath);
    VideoNoteEditor *createEditor(MainWindow *mw){return new VideoNoteEditor(0, mw);}
    QString exportNote(const ExportStrategy *es, unsigned int level = 0);
};

#endif // VIDEONOTE_H
