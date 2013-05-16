#include "ArticleEditor.h"

void ArticleEditor::BACKEND_ARTICLE_SAVE(){
    BACKEND_ARTICLE_SAVE_TITLE();
    BACKEND_ARTICLE_SAVE_TEXT();
    try{
        nm->saveArticle(*ressource);
        UI_INFORM_USER_OF_SAVE();
    }
    catch(NotesException e){
        qDebug() << e.getInfo();
        QMessageBox::critical(this, "Error", "Your modifications have not been saved!"+e.getInfo());
    }
}

void ArticleEditor::CLOSE_AND_RELEASE_MANAGER(){
    NotesManager::libererInstance();
    this->close();
}

void ArticleEditor::BACKEND_ARTICLE_SAVE_TITLE(){
    QString str = title->text();
    this->ressource->setText(str);
}

void ArticleEditor::BACKEND_ARTICLE_SAVE_TEXT(){
    QString str = text->toPlainText();
    this->ressource->setTitle(str);
}

void ArticleEditor::UI_ENABLE_SAVE_BUTTON(){
    this->btnSave->setEnabled(true);
}

void ArticleEditor::UI_INFORM_USER_OF_SAVE(){
    QMessageBox::information(this, "Article Saved", "Your modifications are saved!");
    this->btnSave->setEnabled(false);
}

ArticleEditor::ArticleEditor(Article* art, QWidget *parent) :
    QWidget(parent), ressource(art)
{
    layout = new QVBoxLayout;
    btnQuit = new QPushButton("Quit", this);
    btnSave = new QPushButton("Save", this);
    title = new QLineEdit(art->getTitle(), this);
    text = new QTextEdit(art->getText(), this);

    this->setLayout(layout);

    layout->addWidget(title);
    layout->addWidget(text);
    layout->addWidget(btnSave);
    layout->addWidget(btnQuit);

    btnSave->setEnabled(false);

    nm = &NotesManager::getInstance();

    QObject::connect(btnQuit, SIGNAL(clicked()), this, SLOT(CLOSE_AND_RELEASE_MANAGER()));
    QObject::connect(title, SIGNAL(textChanged(QString)), this, SLOT(UI_ENABLE_SAVE_BUTTON()));
    QObject::connect(text, SIGNAL(textChanged()), this, SLOT(UI_ENABLE_SAVE_BUTTON()));

    QObject::connect(btnSave, SIGNAL(clicked()), this, SLOT(BACKEND_ARTICLE_SAVE()));
}
