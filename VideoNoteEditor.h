#ifndef VIDEONOTEEDITOR_H
#define VIDEONOTEEDITOR_H

#include "BinaryEditor.h"
class VideoNote;

class VideoNoteEditor : public BinaryEditor
{
public:
    VideoNoteEditor(VideoNote *v, QWidget* parent);
};

#endif // VIDEONOTEEDITOR_H
