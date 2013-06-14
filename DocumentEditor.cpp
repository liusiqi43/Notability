#include "DocumentEditor.h"
#include "Document.h"
#include <QWidget>
#include <QToolBar>
#include "NotesManager.h"
#include "NoteTypeSignalAction.h"
#include "mainwindow.h"

DocumentEditor::DocumentEditor(Document* doc, QWidget *parent)
    :Editor(doc, parent)
{
    NoteTypeSignalAction *actionNewArticle = new NoteTypeSignalAction(article, "&Article", this);
    NoteTypeSignalAction *actionNewAudioNote = new NoteTypeSignalAction(audioNote, "&AudioNote", this);
    NoteTypeSignalAction *actionNewVideoNote = new NoteTypeSignalAction(videoNote, "&VideoNote", this);
    NoteTypeSignalAction *actionNewDocument = new NoteTypeSignalAction(document, "&Document", this);
    NoteTypeSignalAction *actionNewImageNote = new NoteTypeSignalAction(imageNote, "&ImageNote", this);

    actionNewAudioNote->setIcon(QIcon(":images/music"));
    actionNewArticle->setIcon(QIcon(":images/article"));
    actionNewDocument->setIcon(QIcon(":images/document"));
    actionNewImageNote->setIcon(QIcon(":images/image"));
    actionNewVideoNote->setIcon(QIcon(":images/video"));

    toolBar = new QToolBar();
//    toolBar->setBackgroundRole(QPalette::NColorRoles);
    toolBar->addAction(actionNewArticle);
    toolBar->addAction(actionNewImageNote);
    toolBar->addAction(actionNewAudioNote);
    toolBar->addAction(actionNewVideoNote);
    toolBar->addAction(actionNewDocument);
    for(QList<Note*>::const_iterator it = doc->begin(); it != doc->end(); ++it){
        contentLayout->addWidget((*it)->createAndAttachEditor());
    }

    QObject::connect(actionNewArticle, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewDocument, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewImageNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewAudioNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewVideoNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    contentLayout->addWidget(toolBar);
}

void DocumentEditor::BACKEND_SET_CONTENT()
{
}

void DocumentEditor::UI_NEW_NOTE_EDITOR(const int type)
{
    NoteType nt;
    try{
        nt = static_cast<NoteType>(type);
    }catch(std::bad_cast& bc){
        QMessageBox::critical(this, "Error", "something serious happenned during creation of new editor..."+QString(bc.what()));
    }
    try{
        Note* temp = &NotesManager::getInstance().getNewNote(nt);
        Editor* noteEditor = temp->createAndAttachEditor();
        noteEditor->setDocumentBtnText(this->getRessource()->getTitle());
        this->getRessource()->addNote(temp);
        contentLayout->removeWidget(toolBar);
        contentLayout->addWidget(noteEditor);
        contentLayout->addWidget(toolBar);
        MainWindow::getInstance()->addRessources(temp);
    }
    catch(NotesException e){
        QMessageBox::critical(this, "Error", e.getInfo());
    }
    MainWindow::getInstance()->updateSideBar();
}

