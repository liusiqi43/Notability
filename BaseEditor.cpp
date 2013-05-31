#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QInputDialog>

#include "Note.h"
#include "Editor.h"
#include "mainwindow.h"
#include "NotesException.h"
#include "NotesManager.h"
#include "htmlViewer.h"
#include "TagManager.h"
#include "Tag.h"

Editor::Editor(Note *n, QWidget *parent) :
    QWidget(parent), ressource(n)
{
    btnSave = new QPushButton("Save");
    btnClose= new QPushButton("Close");
    btnMove = new QPushButton("Move");
    btnTag = new QPushButton("Tag");

    titleWidget = new QLineEdit(ressource->getTitle());
    contentWidget = new QWidget();
    buttonsWidget = new QWidget();

    editorBaseLayout = new QVBoxLayout();
    contentLayout = new QVBoxLayout();
    buttonsLayout = new QHBoxLayout();

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    editorBaseLayout->addWidget(new QLabel("Title:"));
    editorBaseLayout->addWidget(titleWidget);
    editorBaseLayout->addWidget(buttonsWidget);
    editorBaseLayout->addWidget(contentWidget);
    editorBaseLayout->addWidget(line);

    this->setLayout(editorBaseLayout);
    contentWidget->setLayout(contentLayout);
    buttonsWidget->setLayout(buttonsLayout);

    buttonsLayout->addWidget(btnSave);
    buttonsLayout->addWidget(btnClose);
    buttonsLayout->addWidget(btnMove);
    buttonsLayout->addWidget(btnTag);
    btnSave->setEnabled(false);


    QObject::connect(titleWidget, SIGNAL(textChanged(QString)), this, SLOT(UI_ENABLE_SAVE_BUTTON_AND_UPDATE_SIDEBAR()));
    QObject::connect(btnSave, SIGNAL(clicked()),this, SLOT(BACKEND_SAVE()));
    QObject::connect(btnTag, SIGNAL(clicked()), this, SLOT(ADD_TAG_TO_NOTE()));
}

void Editor::ADD_TAG_TO_NOTE()
{
    QString pseudo = QInputDialog::getText(NULL, "Tag", "Quel est le tag auquel vous voulez associé la note ?");
    Tag tag(pseudo);
    tag.addNote(this->getRessource());
}

void Editor::UI_ENABLE_SAVE_BUTTON_AND_UPDATE_SIDEBAR()
{
    BACKEND_SET_TITLE();
    MainWindow::getInstance()->updateSideBar();
    this->btnSave->setEnabled(true);
}

void Editor::BACKEND_SET_TITLE()
{
    QString str = titleWidget->text();
    this->ressource->setTitle(str);
}

void Editor::BACKEND_SET()
{
    BACKEND_SET_TITLE();
    BACKEND_SET_CONTENT();
}

void Editor::BACKEND_SAVE()
{
    BACKEND_SET();
    try{
        NotesManager *nm = &NotesManager::getInstance();
//        ressource->save();
        nm->saveNote(*ressource);
        UI_INFORM_USER_OF_SAVE();
    }
    catch(NotesException e){
//        qDebug() << e.getInfo();
        QMessageBox::critical(this, "Error", "Your modifications have not been saved! Error: "+e.getInfo());
    }
}

void Editor::UI_INFORM_USER_OF_SAVE(){
    QMessageBox::information(this, "Article Saved", "Your modifications have been saved!");
    this->btnSave->setEnabled(false);
}

QLineEdit *Editor::getTitleWidget() const
{
    return titleWidget;
}

void Editor::setTitleWidget(QLineEdit *value)
{
    titleWidget = value;
}

Note *Editor::getRessource() const
{
    return ressource;
}

void Editor::setRessource(Note *value)
{
    ressource = value;
}

bool Editor::operator ==(const Editor &rhs)
{
    return this->getRessource()->getFilePath() == rhs.getRessource()->getFilePath();
}
