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

    videoWidget = new Player(this);

//    videoWidget->setMinimumHeight(this->height()/2);

    if(!ressource->getMediaPath().isNull())
    {
        videoWidget->openMedia(QUrl::fromLocalFile(ressource->getMediaPath()));
    }
    contentLayout->addWidget(videoWidget);
    contentLayout->addWidget(new QLabel("Description:"));
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
    if(!ressource->getMediaPath().isNull())
        videoWidget->openMedia(QUrl::fromLocalFile(ressource->getMediaPath()));
}

void VideoNoteEditor::CLOSING()
{
    videoWidget->stop();
}
