#include "AudioNoteEditor.h"
#include "AudioNote.h"
#include <QWidget>

AudioNoteEditor::AudioNoteEditor(AudioNote* a, QWidget *parent = 0)
    :BinaryEditor(a, parent)
{}
