#include "VideoNoteEditor.h"
#include "VideoNote.h"
#include <QWidget>


VideoNoteEditor::VideoNoteEditor(VideoNote *v, MainWindow *mw, QWidget* parent)
    :BinaryEditor(v, mw, parent)
{
}

void VideoNoteEditor::BACKEND_SET_CONTENT()
{
}
