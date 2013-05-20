#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

#include "Notes.h"
#include "BaseEditor.h"

Editor::Editor(Note *n, QWidget *parent) :
    QWidget(parent), ressource(n)
{
    btnSave = new QPushButton("Save");
    titleWidget = new QLineEdit(ressource->getTitle());
    layout = new QVBoxLayout();
    layout->addWidget(titleWidget);

    this->setLayout(layout);

    QObject::connect(titleWidget, SIGNAL(textChanged(QString)), this, SLOT(UI_ENABLE_SAVE_BUTTON()));
    QObject::connect(btnSave, SIGNAL(clicked()),this, SLOT(BACKEND_SAVE()));
}

void Editor::UI_ENABLE_SAVE_BUTTON()
{
    this->btnSave->setEnabled(true);
}

void Editor::BACKEND_SAVE_TITLE()
{
    QString str = titleWidget->text();
    this->ressource->setTitle(str);
}


void Editor::BACKEND_SAVE()
{
    BACKEND_SAVE_TITLE();
    BACKEND_SET_CONTENT();
    try{
        ressource->save();
        UI_INFORM_USER_OF_SAVE();
    }
    catch(NotesException e){
        qDebug() << e.getInfo();
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

QPushButton *Editor::getBtnSave() const
{
    return btnSave;
}

void Editor::setBtnSave(QPushButton *value)
{
    btnSave = value;
}
