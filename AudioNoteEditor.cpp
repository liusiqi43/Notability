#include "AudioNoteEditor.h"
#include "AudioNote.h"
#include <QWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUrl>
#include <QProgressBar>

AudioNoteEditor::AudioNoteEditor(AudioNote* a, QWidget *parent)
    :BinaryEditor(a, parent), ressource(a)
{
    btnAddAudio = new QPushButton("Choose a Song");

    player = new QMediaPlayer;
    playlist = new QMediaPlaylist(player);

    if(!ressource->getMediaPath().isNull())
    {
        playlist->addMedia(QUrl::fromLocalFile(ressource->getMediaPath()));
        player->setMedia(QUrl::fromLocalFile(ressource->getMediaPath()));
        playlist->setCurrentIndex(0);
        player->setPlaylist(playlist);
        play = false;
        btnPlayPause = new QPushButton("PLay/Pause");
        btnStop = new QPushButton("Stop");
        btnStop->resize(32,32);
        btnStop->setIcon(QIcon("Icons/stop.png"));
        progression = new QProgressBar;
        progression->setMinimum(0);
        progression->setMaximum(100);
        btnPlayPause->setIcon(QIcon("Icons/play.png"));
        QObject::connect(btnPlayPause, SIGNAL(clicked()), this, SLOT(PLAY_PAUSE_SONG()));
        QObject::connect(btnStop, SIGNAL(clicked()), this, SLOT(STOP_SONG()));
        //QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(SET_VALUE(qint64)));
        qDebug() << player->position();
    }

    btnLine = new QHBoxLayout;
    contentLayout->addLayout(btnLine);
    btnLine->addWidget(btnPlayPause);
    btnLine->addWidget(btnStop);
    btnLine->addWidget(progression);

    contentLayout->addWidget(new QLabel("Description:"));

    contentLayout->addWidget(getDescriptionWidget());
    buttonsLayout->addWidget(btnAddAudio);

    QObject::connect(btnAddAudio, SIGNAL(clicked()), this, SLOT(LOAD_AUDIO()));
    QObject::connect(this, SIGNAL(destroyed()), this, SLOT(CLOSING()));
}

AudioNoteEditor::~AudioNoteEditor(){
    player->stop();
}

void AudioNoteEditor::CLOSING()
{
    player->stop();
}

void AudioNoteEditor::BACKEND_SET_CONTENT()
{
    ressource->setDescription(getDescriptionWidget()->text());
    ressource->setMediaPath(ressource->getMediaPath());
}

void AudioNoteEditor::LOAD_AUDIO(){
    ressource->setMediaPath(QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Audio (*.mp3 *.ogg)"));
    qDebug()<<ressource->getMediaPath();

    player->setMedia(QMediaContent(QUrl::fromLocalFile(ressource->getMediaPath())));

    player->setMedia(QUrl::fromLocalFile(ressource->getMediaPath()));
    play = false;

}

void AudioNoteEditor::PLAY_PAUSE_SONG()
{

    if(play)
    {
        player->pause();
        btnPlayPause->setIcon(QIcon("play.png"));
        play = false;
    }
    else
    {
        player->play();
        btnPlayPause->setIcon(QIcon("pause.png"));
        play = true;
    }
}

void AudioNoteEditor::STOP_SONG()
{
    player->stop();
}

void AudioNoteEditor::SET_VALUE(qint64 val)
{
    int v;
    //v= int(val)*100/int(val);
    v = static_cast<int>(val)*100/static_cast<int>(val);
    progression->setValue(v);
}

