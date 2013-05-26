#include "ImageNoteEditor.h"
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include "ImageNote.h"
/***
 * ImageNoteEditor
 */

//ImageNote *ImageNoteEditor::getRessource() const
//{
//    return ressource;
//}

//void ImageNoteEditor::setRessource(ImageNote *value)
//{
//    ressource = value;
//}

QString ImageNoteEditor::toHtml() const
{
    return "<html><head><meta charset=\"UTF-8\"><title>"+
            getTitleWidget()->text()+"</title></head><body>"+
            "<h1>"+getTitleWidget()->text()+"</h1>"
            +"<img style=\"width: 100%\" src=\"file://"+ currentImgPath +"\" alt=\"\"><p>"
            +getDescriptionWidget()->text()+"</p></body></html>";
}

void ImageNoteEditor::BACKEND_SET_CONTENT()
{
    ressource->setDescription(getDescriptionWidget()->text());
    ressource->setMediaPath(currentImgPath);
}

void ImageNoteEditor::LOAD_IMAGE(){
    currentImgPath = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.jpeg *.xpm *.jpg)");
    image = QPixmap(currentImgPath);
    if(!image.isNull()){
        imageWidget->setPixmap(image);
    }
}

ImageNoteEditor::ImageNoteEditor(ImageNote *img, QWidget *parent)
    :BinaryEditor(img, parent), ressource(img), currentImgPath(img->getMediaPath())
{
    btnAddImage = new QPushButton("Add");

    image = QPixmap(ressource->getMediaPath());
    imageWidget = new QLabel();
    imageWidget->setScaledContents(true);
    if(!image.isNull()){
        imageWidget->setPixmap(image);
    }
    layout->addWidget(imageWidget);
    layout->addWidget(getDescriptionWidget());
    layout->addWidget(btnAddImage);
    layout->addWidget(getBtnSave());
    this->setLayout(layout);

    QObject::connect(btnAddImage, SIGNAL(clicked()), this, SLOT(LOAD_IMAGE()));
}
