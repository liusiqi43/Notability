#ifndef AUDIONOTEEDITOR_H
#define AUDIONOTEEDITOR_H

#include "BinaryEditor.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

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
    void PLAY_STOP_VIDEO();

private:
    QPushButton *btnAddAudio;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    AudioNote *ressource;
    QPushButton *btnPlayStop;
    bool play;

};

#endif // AUDIONOTEEDITOR_H
