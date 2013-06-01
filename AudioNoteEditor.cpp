#include "AudioNoteEditor.h"
#include "AudioNote.h"
#include <QWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>

AudioNoteEditor::AudioNoteEditor(AudioNote* a, QWidget *parent)
    :BinaryEditor(a, parent), ressource(a), currentAudioPath(a->getMediaPath())
{
    btnAddAudio = new QPushButton("Choose a Song");

    audio = QPixmap(ressource->getMediaPath());
    audioWidget = new QLabel();
    audioWidget->setScaledContents(true);
    if(!audio.isNull()){
        audioWidget->setPixmap(audio);
    }
    contentLayout->addWidget(audioWidget);
    contentLayout->addWidget(new QLabel("Description:"));
    contentLayout->addWidget(getDescriptionWidget());
    buttonsLayout->addWidget(btnAddAudio);



    QObject::connect(btnAddAudio, SIGNAL(clicked()), this, SLOT(LOAD_AUDIO()));
}

void AudioNoteEditor::BACKEND_SET_CONTENT()
{
    ressource->setDescription(getDescriptionWidget()->text());
    ressource->setMediaPath(currentAudioPath);
}

void AudioNoteEditor::LOAD_AUDIO(){
    currentAudioPath = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Audio (*.mp3)");
    audio = QPixmap(currentAudioPath);
    if(!audio.isNull()){
        audioWidget->setPixmap(audio);
    }
}
