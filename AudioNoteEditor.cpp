#include "AudioNoteEditor.h"
#include "AudioNote.h"
#include <QWidget>

AudioNoteEditor::AudioNoteEditor(AudioNote* a, QWidget *parent)
    :BinaryEditor(a, parent)
{}

void AudioNoteEditor::BACKEND_SET_CONTENT()
{
}
