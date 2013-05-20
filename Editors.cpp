#include "Editors.h"
#include "NotesManager.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QObject>

void ArticleEditor::BACKEND_SET_CONTENT(){
    QString str = textWidget->toHtml();
    this->ressource->setText(str);
}

ArticleEditor::ArticleEditor(Article *art, QWidget *parent) :
    Editor(art, parent), ressource(art)
{
    textWidget = new QTextEdit(ressource->getText());

    layout->addWidget(textWidget);
    layout->addWidget(getBtnSave());

    getBtnSave()->setEnabled(false);

    this->setLayout(layout);

    QObject::connect(textWidget, SIGNAL(textChanged()), this, SLOT(UI_ENABLE_SAVE_BUTTON()));
}

QTextEdit *ArticleEditor::getTextWidget() const
{
    return textWidget;
}

void ArticleEditor::setTextWidget(QTextEdit *value)
{
    textWidget = value;
}

Article *ArticleEditor::getRessource() const
{
    return ressource;
}

void ArticleEditor::setRessource(Article *value)
{
    ressource = value;
}

QString ArticleEditor::toHtml() const
{
    return "<html><head><meta charset=\"UTF-8\"><title>"+
            getTitleWidget()->text()+"</title></head><body>"+
            "<h1>"+getTitleWidget()->text()+"</h1>"+
            getTextWidget()->toHtml()+"</body></html>";
}

/***
 * BinaryEditor
 */

Binary *BinaryEditor::getRessource() const
{
    return ressource;
}

void BinaryEditor::setRessource(Binary *value)
{
    ressource = value;
}

QLineEdit *BinaryEditor::getDescriptionWidget() const
{
    return descriptionWidget;
}

void BinaryEditor::setDescriptionWidget(QLineEdit *value)
{
    descriptionWidget = value;
}

BinaryEditor::BinaryEditor(Binary *b, QWidget *parent)
    :Editor(b, parent), ressource(b)
{
    descriptionWidget = new QLineEdit(ressource->getDescription());
}

/***
 * ImageNoteEditor
 */

ImageNote *ImageNoteEditor::getRessource() const
{
    return ressource;
}

void ImageNoteEditor::setRessource(ImageNote *value)
{
    ressource = value;
}

QString ImageNoteEditor::toHtml() const
{
    return "<html><head><meta charset=\"UTF-8\"><title>"+
            getTitleWidget()->text()+"</title></head><body>"+
            "<h1>"+getTitleWidget()->text()+"</h1>"
            +"<img style=\"width: 100%\" src=\""+ currentImgPath +"\" alt=\"\"><p>"
            +getDescriptionWidget()->text()+"</p></body></html>";
}

void ImageNoteEditor::BACKEND_SET_CONTENT()
{
    ressource->setDescription(getDescriptionWidget()->text());
    ressource->setImgPath(currentImgPath);
}

void ImageNoteEditor::LOAD_IMAGE(){
    currentImgPath = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.xpm *.jpg)");
    image = QPixmap(currentImgPath);
    if(!image.isNull()){
        imageWidget->setPixmap(image);
    }
}

ImageNoteEditor::ImageNoteEditor(ImageNote *img, QWidget *parent)
    :BinaryEditor(img, parent), ressource(img), currentImgPath(img->getImgPath())
{
    btnAddImage = new QPushButton("Add");

    image = QPixmap(ressource->getImgPath());
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

