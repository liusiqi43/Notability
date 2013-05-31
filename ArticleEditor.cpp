#include "ArticleEditor.h"
#include "Article.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

void ArticleEditor::BACKEND_SET_CONTENT(){
    QString str = textWidget->toPlainText();
//    qDebug()<<str;
    this->ressource->setText(str);
}

ArticleEditor::ArticleEditor(Article *art, QWidget *parent) :
    Editor(art, parent), ressource(art)
{
    textWidget = new QPlainTextEdit(ressource->getText());

    contentLayout->addWidget(new QLabel("Text:"));
    contentLayout->addWidget(textWidget);

    QObject::connect(textWidget, SIGNAL(textChanged()), this, SLOT(UI_ENABLE_SAVE_BUTTON_AND_UPDATE_SIDEBAR()));
}

QPlainTextEdit *ArticleEditor::getTextWidget() const
{
    return textWidget;
}

void ArticleEditor::setTextWidget(QPlainTextEdit *value)
{
    textWidget = value;
}
