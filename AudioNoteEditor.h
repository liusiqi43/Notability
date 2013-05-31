#ifndef AUDIONOTEEDITOR_H
#define AUDIONOTEEDITOR_H

#include "BinaryEditor.h"
class AudioNote;

class AudioNoteEditor : public BinaryEditor
{
    Q_OBJECT
public:
    explicit AudioNoteEditor(AudioNote *a, QWidget *parent = 0);

signals:

public slots:
    void BACKEND_SET_CONTENT();
    void LOAD_AUDIO();

private:
    QPushButton *btnAddAudio;
    QPixmap audio;
    QLabel *audioWidget;
    AudioNote *ressource;
    QString currentAudioPath;

};

#endif // AUDIONOTEEDITOR_H
