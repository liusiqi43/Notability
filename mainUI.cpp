#include "mainUI.h"
#include "NoteFactory.h"
#include "NoteTypeSignalAction.h"
#include "NotesManager.h"
#include "Editor.h"
#include "NotesException.h"
#include "Note.h"
#include "ExportStrategy.h"
#include "htmlViewer.h"
#include <typeinfo>
#include <QMap>

void mainUI::UI_INFORM_NOT_IMPLEMENTED(){
    QMessageBox::information(this, "New fonctionality", "To be implemented...");
}


void mainUI::UI_NEW_NOTE_EDITOR(const int type){

    NoteType nt;
    try{
        nt = static_cast<NoteType>(type);
    }catch(std::bad_cast& bc){
        QMessageBox::critical(this, "Error", "something serious happenned during creation of new editor..."+QString(bc.what()));
    }

    if(EditorPage->layout()){
        delete noteEditor;
        delete EditorPage->layout();
    }

    nm = &NotesManager::getInstance();
    try{
        ressource = &nm->getNewNote(nt);
        noteEditor = ressource->createEditor();
        QVBoxLayout *parentLayout = new QVBoxLayout();
        EditorPage->setLayout(parentLayout);
        parentLayout->addWidget(noteEditor);
    }
    catch(NotesException e){
        QMessageBox::critical(this, "Error", e.getInfo());
    }
}


void mainUI::UI_OPEN_FILE(){

    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Notes (*.txt *.img *.vid *.aud *.doc)");

    if(!fichier.isNull()){
        if(EditorPage->layout()){
            delete noteEditor;
            delete EditorPage->layout();
        }

        nm = &NotesManager::getInstance();
        try{
            ressource = &nm->getNote(fichier);
            noteEditor = ressource->createEditor();
            QVBoxLayout *parentLayout = new QVBoxLayout();
            EditorPage->setLayout(parentLayout);
            parentLayout->addWidget(noteEditor);
        }
        catch(NotesException e){
            QMessageBox::critical(this, "Error", e.getInfo());
        }
    }
}

void mainUI::UI_TAB_CHANGE_HANDLER(int n){
    switch(n){
    case -1:{
        return;
    }
    case 1:{
        qDebug()<<"HTML";
        this->noteEditor->BACKEND_SET();
        QString HTML = ressource->exportNote(NotesManager::strategies[html]);
        if(htmlViewerPage->layout()){
            delete hv;
            delete htmlViewerPage->layout();
        }

        // add html viewer into tab
        hv = new HtmlViewer(HTML);
        QVBoxLayout *parentLayoutHV = new QVBoxLayout();
        parentLayoutHV->addWidget(hv);
        htmlViewerPage->setLayout(parentLayoutHV);
        break;
    }
    case 2:{
        qDebug()<<"TeX";
        //        this->noteEditor->BACKEND_SET();
        //        QString html = ressource->exportNote(NotesManager::strategies[html]);
        //        if(htmlViewerPage->layout()){
        //            delete hv;
        //            delete htmlViewerPage->layout();
        //        }

        //        // add html viewer into tab
        //        hv = new HtmlViewer(html);
        //        QVBoxLayout *parentLayoutHV = new QVBoxLayout();
        //        parentLayoutHV->addWidget(hv);
        //        htmlViewerPage->setLayout(parentLayoutHV);
        break;
    }
    default:
        return;
    }
}

mainUI::mainUI(QWidget *parent) :
        QMainWindow(parent)
{
    mainWidget = new QWidget;
    QToolBar *toolBar = addToolBar("General");
    QAction *actionQuit = new QAction("&Quit", this);
    QAction *actionOpen = new QAction("&Open...", this);

    NoteTypeSignalAction *actionNewArticle = new NoteTypeSignalAction(article, "&Article", this);
    NoteTypeSignalAction *actionNewAudioNote = new NoteTypeSignalAction(audioNote, "&AudioNote", this);
    NoteTypeSignalAction *actionNewVideoNote = new NoteTypeSignalAction(videoNote, "&VideoNote", this);
    NoteTypeSignalAction *actionNewDocument = new NoteTypeSignalAction(document, "&Document", this);
    NoteTypeSignalAction *actionNewImageNote = new NoteTypeSignalAction(imageNote, "&ImageNote", this);
    QMenu *menuNew = new QMenu("&New...");
    menuNew->addAction(actionNewArticle);
    menuNew->addAction(actionNewImageNote);
    menuNew->addAction(actionNewVideoNote);
    menuNew->addAction(actionNewAudioNote);
    menuNew->addAction(actionNewDocument);

    menuFichier = menuBar()->addMenu("&File");
    menuEdition = menuBar()->addMenu("&Edit");

    menuFichier->addMenu(menuNew);
    menuFichier->addAction(actionOpen);

    menuFichier->addAction(actionQuit);
    toolBar->addAction(actionOpen);
    toolBar->addAction(actionQuit);

    tab = new QTabWidget();
    EditorPage = new QWidget();
    htmlViewerPage = new QWidget();
    texViewerPage = new QWidget();

    // Creat a new article, with generated file path and empty title&text
    // TODO add article to a default document.
    nm = &NotesManager::getInstance();
    //    ressource = &nm->getNewArticle();
    ressource = &nm->getNewNote(article);

    // add default article editor into layout
    QVBoxLayout *parentLayout = new QVBoxLayout();
    EditorPage->setLayout(parentLayout);
    noteEditor = ressource->createEditor();
    parentLayout->addWidget(noteEditor);

    tab->addTab(EditorPage, "Editor");
    tab->addTab(htmlViewerPage, "HTML");
    tab->addTab(texViewerPage, "TeX");

    layout = new QVBoxLayout();
    layout->addWidget(tab);

    mainWidget->setLayout(layout);

    this->setCentralWidget(mainWidget);
    qDebug()<<"Hello";
    QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionOpen, SIGNAL(triggered()), this, SLOT(UI_OPEN_FILE()));
    QObject::connect(actionNewArticle, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewDocument, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewImageNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewAudioNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewVideoNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));

    // Tab change handling
    QObject::connect(tab, SIGNAL(currentChanged(int)), this, SLOT(UI_TAB_CHANGE_HANDLER(int)));
}
