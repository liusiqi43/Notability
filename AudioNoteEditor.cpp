#include "AudioNoteEditor.h"
#include "AudioNote.h"
#include <QWidget>

AudioNoteEditor::AudioNoteEditor(AudioNote* a, MainWindow *mw, QWidget *parent)
    :BinaryEditor(a, mw, parent)
{}

void AudioNoteEditor::BACKEND_SET_CONTENT()
{
}
