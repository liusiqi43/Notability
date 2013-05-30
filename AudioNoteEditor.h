#ifndef AUDIONOTEEDITOR_H
#define AUDIONOTEEDITOR_H

#include "BinaryEditor.h"
class AudioNote;

class AudioNoteEditor : public BinaryEditor
{
    Q_OBJECT
public:
    explicit AudioNoteEditor(AudioNote *a, MainWindow *mw, QWidget *parent = 0);

signals:
public slots:
    void BACKEND_SET_CONTENT();

private:
};

#endif // AUDIONOTEEDITOR_H
