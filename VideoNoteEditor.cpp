#include "VideoNoteEditor.h"
#include "VideoNote.h"
#include <QWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QUrl>
#include <QDebug>


VideoNoteEditor::VideoNoteEditor(VideoNote *v, QWidget* parent)
    :BinaryEditor(v, parent), ressource(v)
{
    btnAddVideo = new QPushButton("Choose a Video");

    player = new QMediaPlayer;
    playlist = new QMediaPlaylist(player);
    videoWidget = new QVideoWidget();

    if(!ressource->getMediaPath().isNull())
    {
    playlist->addMedia(QUrl::fromLocalFile(ressource->getMediaPath()));
    player->setVideoOutput(videoWidget);
    playlist->setCurrentIndex(0);
    player->setPlaylist(playlist);
    player->play();
    }
    contentLayout->addWidget(videoWidget);
    contentLayout->addWidget(getDescriptionWidget());
    buttonsLayout->addWidget(btnAddVideo);



    QObject::connect(btnAddVideo, SIGNAL(clicked()), this, SLOT(LOAD_VIDEO()));

}

void VideoNoteEditor::BACKEND_SET_CONTENT()
{
    ressource->setDescription(getDescriptionWidget()->text());
    ressource->setMediaPath(ressource->getMediaPath());
}

void VideoNoteEditor::LOAD_VIDEO(){
    ressource->setMediaPath(QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Video (*.mp4 *.avi)"));
    qDebug()<<ressource->getMediaPath();

    player->setMedia(QMediaContent(QUrl::fromLocalFile(ressource->getMediaPath())));

    qDebug()<<"hello";
    player->setVideoOutput(videoWidget);
    qDebug()<<"hello";
    player->play();
}
