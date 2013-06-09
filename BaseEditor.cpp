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

#include "AddToDocDialog.h"
#include "AddTagToNoteDialog.h"
#include "Trash.h"
#include "TreeItem.h"

#include "BinaryEditor.h"
#include <QListView>
#include <QComboBox>


Editor::Editor(Note *n, QWidget *parent) :
    QWidget(parent), ressource(n), documentBtn(0), tagDialog(0), docDialog(0)
{
    MainWindow *mw = MainWindow::getInstance();

    mw->addOpenedFiles(ressource->getFilePath());
    mw->addRessources(ressource);

    btnSave = new QPushButton("Save");
    btnClose= new QPushButton("Close");
    btnDelete = new QPushButton("Delete");
    btnTag = new QPushButton("Tag");
    documentBtn = new QPushButton("~");
    btnSave->setIcon(QIcon(":images/save"));
    btnDelete->setIcon(QIcon(":images/supprimer"));
    btnTag->setIcon(QIcon(":images/tag"));
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
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Expanding, QSizePolicy::DefaultType);
    QWidget* bottomspacer = new QWidget();
    bottomspacer->setSizePolicy(policy);
    editorBaseLayout->addWidget(bottomspacer);
    editorBaseLayout->addWidget(line);

    this->setLayout(editorBaseLayout);
    titleWidget->setLayout(titleLayout);
    contentWidget->setLayout(contentLayout);
    buttonsWidget->setLayout(buttonsLayout);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    buttonsLayout->addWidget(spacer);
    buttonsLayout->addWidget(btnSave);
    buttonsLayout->addWidget(btnClose);
    buttonsLayout->addWidget(btnDelete);
    buttonsLayout->addWidget(btnTag);
    btnSave->setEnabled(false);

    QObject::connect(titleEditWidget, SIGNAL(textChanged(QString)), this, SLOT(UI_ENABLE_SAVE_BUTTON_AND_UPDATE_SIDEBAR()));
    QObject::connect(btnSave, SIGNAL(clicked()),this, SLOT(BACKEND_SAVE()));
    QObject::connect(documentBtn, SIGNAL(clicked()),this, SLOT(FIRE_UP_DOC_DIALOG()));
    QObject::connect(btnTag, SIGNAL(clicked()), this, SLOT(ADD_TAG_TO_NOTE()));
    QObject::connect(btnDelete, SIGNAL(clicked()), this, SLOT(REMOVE_NOTE_TO_TRASH()));
}

void Editor::ADD_TAG_TO_NOTE()
{
    tagDialog = new AddTagToNoteDialog(this->ressource);
    tagDialog->show();
    QObject::connect(tagDialog, SIGNAL(accepted()), this, SLOT(retrieveDataFromTagDialog()));
}


void Editor::retrieveDataFromTagDialog()
{
    qDebug()<<"Retrieving data...";
    TagManager *tm = &TagManager::getInstance();
    QSet<Tag *> *newEnclosingTags = tagDialog->getTags();
    for(tagSetIt it = tm->begin(); it!=tm->end(); ++it){
        if(newEnclosingTags->contains(*it)){
            if(!(*it)->getAssocs().contains(this->ressource)){
                tm->addTagToNote((*it), ressource);
            }
        }
        else{
            tm->removeTagForNote((*it), ressource);
        }
    }
    MainWindow::getInstance()->updateSideBar();
    delete tagDialog;
    tagDialog = 0;
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

bool Editor::operator==(const Editor &rhs)
{
    return this->getRessource()->getFilePath() == rhs.getRessource()->getFilePath();
}

void Editor::setTitleWidgetText(const QString &title)
{
    titleEditWidget->setText(title);
}

void Editor::FIRE_UP_DOC_DIALOG(){
    docDialog = new AddToDocDialog(this->ressource);
    docDialog->show();
    QObject::connect(docDialog, SIGNAL(accepted()), this, SLOT(retrieveDataFromDocDialog()));
}

void Editor::retrieveDataFromDocDialog()
{
    qDebug()<<"Retrieving data...";
    NotesManager *nm = &NotesManager::getInstance();
    QSet<Document *> * newEnclosingDocuments = docDialog->getDocuments();
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
    delete docDialog;
    docDialog = 0;
}

void Editor::REMOVE_NOTE_TO_TRASH()
{
    BinaryEditor * binEditor = 0;
    try{
        binEditor = dynamic_cast<BinaryEditor *>(this);
    } catch (std::bad_cast e){}
    if(binEditor)
        binEditor->CLOSING();
    ressource->setEditor(0);
    Trash::getInstance()->recycle(ressource);
    MainWindow::getInstance()->removeRessource(ressource);
    ressource = 0;
    this->close();
}
