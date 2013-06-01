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

#include "CheckComboBox.h"
#include "AddToDocDialog.h"
#include "TreeItem.h"
#include <QListView>
#include <QComboBox>


Editor::Editor(Note *n, QWidget *parent) :
    QWidget(parent), ressource(n), documentBtn(0)
{
    MainWindow *mw = MainWindow::getInstance();

    mw->addOpenedFiles(ressource->getFilePath());
    mw->addRessources(ressource);

    btnSave = new QPushButton("Save");
    btnClose= new QPushButton("Close");
    btnMove = new QPushButton("Move");
    btnTag = new QPushButton("Tag");
    documentBtn = new QPushButton("~");

    titleEditWidget = new QLineEdit(ressource->getTitle());


    titleWidget = new QWidget();
    contentWidget = new QWidget();
    buttonsWidget = new QWidget();

    editorBaseLayout = new QVBoxLayout();
    titleLayout = new QHBoxLayout();
    contentLayout = new QVBoxLayout();
    buttonsLayout = new QHBoxLayout();

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    //    updateDocBtnWithRessource();

    editorBaseLayout->addWidget(new QLabel("Title:"));

    titleLayout->addWidget(documentBtn);
    titleLayout->addWidget(new QLabel("/"));
    titleLayout->addWidget(titleEditWidget);

    editorBaseLayout->addWidget(titleWidget);
    editorBaseLayout->addWidget(buttonsWidget);
    editorBaseLayout->addWidget(contentWidget);
    editorBaseLayout->addWidget(line);

    this->setLayout(editorBaseLayout);
    titleWidget->setLayout(titleLayout);
    contentWidget->setLayout(contentLayout);
    buttonsWidget->setLayout(buttonsLayout);

    buttonsLayout->addWidget(btnSave);
    buttonsLayout->addWidget(btnClose);
    buttonsLayout->addWidget(btnMove);
    buttonsLayout->addWidget(btnTag);
    btnSave->setEnabled(false);

    QObject::connect(titleEditWidget, SIGNAL(textChanged(QString)), this, SLOT(UI_ENABLE_SAVE_BUTTON_AND_UPDATE_SIDEBAR()));
    QObject::connect(btnSave, SIGNAL(clicked()),this, SLOT(BACKEND_SAVE()));

    QObject::connect(btnTag, SIGNAL(clicked()), this, SLOT(ADD_TAG_TO_NOTE()));
}

void Editor::ADD_TAG_TO_NOTE()
{
    bool ok = false;
    TagManager& c=TagManager::getInstance();
    QString newTag = QInputDialog::getText(NULL, "Tag", "Quel est le tag auquel vous voulez associé la note ?",QLineEdit::Normal, QString(), &ok);

    if (ok && !newTag.isEmpty())
    {
        qDebug()  << newTag;
        Tag* tag = new Tag(newTag);
        tag->addNote(this->getRessource());
        qDebug() << this->getRessource();
        MainWindow::getInstance()->updateTagList();
    }

    QObject::connect(documentBtn, SIGNAL(clicked()),this, SLOT(FIRE_UP_DOC_DIALOG()));

}

void Editor::UI_ENABLE_SAVE_BUTTON_AND_UPDATE_SIDEBAR()
{
    BACKEND_SET_TITLE();
    MainWindow::getInstance()->updateSideBar();
    this->btnSave->setEnabled(true);
}

void Editor::BACKEND_SET_TITLE()
{
    QString str = titleEditWidget->text();
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

void Editor::updateDocBtnWithRessource(TreeItem *item)
{
    TreeItem *parent = item->parent();
    qDebug()<<"parent data:"<<parent->data(0).toString();
    item->getItemId()->getEditor()->setDocumentBtnText(parent->data(0).toString());
    parent = item;
    qDebug()<<"new parent data:"<<parent->data(0).toString();

    if(parent){
        for(int i = 0; i<parent->childCount();i++){
            Note* current = parent->child(i)->getItemId();
            qDebug()<<"currentTItle:"<<current->getTitle();
            if(current->isDocument())
                updateDocBtnWithRessource(parent->child(i));
            else
                current->getEditor()->setDocumentBtnText(parent->data(0).toString());
        }
    } else {
        throw NotesException("Impossible...pas de parent?");
    }
}

void Editor::setDocumentBtnText(const QString& doc){
    qDebug()<<"Setting docBtn:" << this << " title:" << this->getTitleWidget()->text() << " to "<<doc;
    if(documentBtn)
        documentBtn->setText(doc);
    else
        throw NotesException("documentBtn not found");
}

QLineEdit *Editor::getTitleWidget() const
{
    return titleEditWidget;
}

void Editor::setTitleWidget(QLineEdit *value)
{
    titleEditWidget = value;
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

void Editor::setTitleWidgetText(const QString &title)
{
    titleEditWidget->setText(title);
}

void Editor::FIRE_UP_DOC_DIALOG(){
    dialog = new AddToDocDialog(this->ressource);
    dialog->show();
    QObject::connect(dialog, SIGNAL(accepted()), this, SLOT(retrieveDataFromDocDialog()));
}

void Editor::retrieveDataFromDocDialog()
{
    qDebug()<<"Retrieving data...";
    NotesManager *nm = &NotesManager::getInstance();
    QSet<Document *> * newEnclosingDocuments = dialog->getDocuments();
    for(QSet<Document*>::const_iterator it = nm->beginDocumentContainer(); it!=nm->endDocumentContainer(); ++it){
        if(newEnclosingDocuments->contains(*it)){
            if(!(*it)->contains(this->ressource)){

                try{
                    (*it)->addNote(this->ressource);
                } catch (NotesException e){
                    QMessageBox::critical(0, "Circular Inclusion", e.getInfo());
                }
            }
            this->documentBtn->setText((*it)->getTitle());
        }
        else{
            (*it)->removeNote(this->ressource);
        }
    }
    MainWindow::getInstance()->updateSideBar();
    delete dialog;
    dialog = 0;
}
