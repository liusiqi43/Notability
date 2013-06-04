#include "AudioNoteEditor.h"
#include "AudioNote.h"
#include <QWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUrl>

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
       // player->play();
        btnPlayStop = new QPushButton("PLay/Stop");

        QObject::connect(btnPlayStop, SIGNAL(clicked()), this, SLOT(PLAY_STOP_AUDIO()));
    }

    contentLayout->addWidget(btnPlayStop);
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
    //player->play();
}

void AudioNoteEditor::PLAY_STOP_AUDIO()
{

    if(play)
    {
        player->pause();
        play = false;
    }
    else
    {
        player->play();
        play = true;
    }
}
