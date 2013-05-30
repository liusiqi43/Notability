#include "ImageNoteEditor.h"
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include "ImageNote.h"
/***
 * ImageNoteEditor
 */

void ImageNoteEditor::BACKEND_SET_CONTENT()
{
    ressource->setDescription(getDescriptionWidget()->text());
    ressource->setMediaPath(currentImgPath);
}

void ImageNoteEditor::LOAD_IMAGE(){
    currentImgPath = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.jpeg *.xpm *.jpg)");
    image = QPixmap(currentImgPath);
    int w = imageWidget->width();
    int h = imageWidget->height();

    if(!image.isNull()){
        imageWidget->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
    }
}

ImageNoteEditor::ImageNoteEditor(ImageNote *img, MainWindow *mw, QWidget *parent)
    :BinaryEditor(img, mw, parent), ressource(img), currentImgPath(img->getMediaPath())
{
    btnAddImage = new QPushButton("Picture");

    image = QPixmap(ressource->getMediaPath());
    imageWidget = new QLabel();
    imageWidget->setAlignment(Qt::AlignHCenter);

    int w = imageWidget->width();
    int h = imageWidget->height();

    if(!image.isNull()){
        imageWidget->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
    }
    else {
        imageWidget->setPixmap(QPixmap(":/images/image_not_found").scaled(w, h, Qt::KeepAspectRatio));
    }
    contentLayout->addWidget(imageWidget);
    contentLayout->addWidget(new QLabel("Description:"));
    contentLayout->addWidget(getDescriptionWidget());
    buttonsLayout->addWidget(btnAddImage);

    QObject::connect(btnAddImage, SIGNAL(clicked()), this, SLOT(LOAD_IMAGE()));
}
