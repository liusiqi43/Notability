#include "ArticleEditor.h"
#include "NotesManager.h"

void ArticleEditor::BACKEND_SET_CONTENT(){
    QString str = textWidget->toHtml();
    this->ressource->setText(str);
}

ArticleEditor::ArticleEditor(Note *art, QWidget *parent) :
    Editor(art, parent), ressource(dynamic_cast<Article *>(art))
{
    textWidget = new QTextEdit(ressource->getText());

    layout->addWidget(textWidget);
    layout->addWidget(getBtnSave());

    getBtnSave()->setEnabled(false);

    nm = &NotesManager::getInstance();

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
