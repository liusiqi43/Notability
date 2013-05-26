#ifndef AUDIONOTEEDITOR_H
#define AUDIONOTEEDITOR_H

#include "BinaryEditor.h"
class AudioNote;

class AudioNoteEditor : public BinaryEditor
{
public:
    AudioNoteEditor(AudioNote *a, QWidget *parent);
};

#endif // AUDIONOTEEDITOR_H
