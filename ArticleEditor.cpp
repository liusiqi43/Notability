#include "ArticleEditor.h"
#include "Article.h"
#include <QVBoxLayout>
#include <QPushButton>

void ArticleEditor::BACKEND_SET_CONTENT(){
    QString str = textWidget->toPlainText();
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

//Article *ArticleEditor::getRessource() const
//{
//    return ressource;
//}

//void ArticleEditor::setRessource(Article *value)
//{
//    ressource = value;
//}
