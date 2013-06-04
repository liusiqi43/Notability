#ifndef AUDIONOTEEDITOR_H
#define AUDIONOTEEDITOR_H

#include "BinaryEditor.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QProgressBar>

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
    void PLAY_PAUSE_SONG();
    void STOP_SONG();
    void SET_VALUE(qint64 val);

private:
    QPushButton *btnAddAudio;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    AudioNote *ressource;
    QPushButton *btnPlayPause;
    QPushButton *btnStop;
    QProgressBar *progression;
    QHBoxLayout *btnLine;
    bool play;

};

#endif // AUDIONOTEEDITOR_H
