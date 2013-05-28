#include "mainwindow.h"
#include "NoteFactory.h"
#include "NoteTypeSignalAction.h"
#include "NotesManager.h"
#include "Editor.h"
#include "NotesException.h"
#include "Note.h"
#include "ExportStrategy.h"
#include "htmlViewer.h"
#include "TexViewer.h"
#include "Document.h"
#include "TextViewer.h"
#include "TreeModel.h"
#include <typeinfo>
#include <QMap>
#include <QScrollArea>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    editorWidget = new QWidget;
    ui->editorScroll->setWidget(editorWidget);

    QToolBar *toolBar = addToolBar("General");
    QAction *actionQuit = new QAction("&Quit", this);
    QAction *actionOpen = new QAction("&Open...", this);

    // subclassed QAction, this emets also the NoteType. So that we don't need different handling slot
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
    textViewerPage = new QWidget();

    // Creat a new article, with generated file path and empty title&text
    // TODO add article to a default document.
    nm = &NotesManager::getInstance();
//    ressource = &nm->getNewNote(article);

    // add default article editor into layout
//    QVBoxLayout *parentLayout = new QVBoxLayout();
//    EditorPage->setLayout(parentLayout);
//    noteEditor = ressource->createEditor();
//    parentLayout->addWidget(noteEditor);

    tab->addTab(EditorPage, "Editor");
    tab->addTab(htmlViewerPage, "HTML");
    tab->addTab(texViewerPage, "TeX");
    tab->addTab(textViewerPage, "Text");

//    QScrollArea *scroll = new QScrollArea(mainWidget);
//    scroll->setWidget(tab);

    layout = new QVBoxLayout();
    layout->addWidget(tab);

    editorWidget->setLayout(layout);

//    ui->noteBookTree->setModel(new TreeModel());

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UI_INFORM_NOT_IMPLEMENTED(){
    QMessageBox::information(this, "New fonctionality", "To be implemented...");
}


void MainWindow::UI_NEW_NOTE_EDITOR(const int type){
    NoteType nt;
    QLayout *parentLayout;
    try{
        nt = static_cast<NoteType>(type);
    }catch(std::bad_cast& bc){
        QMessageBox::critical(this, "Error", "something serious happenned during creation of new editor..."+QString(bc.what()));
    }

    if(EditorPage->layout()){
        parentLayout = EditorPage->layout();
        if(notebook == 0){
            notebook = static_cast<Document*>(&nm->getNewNote(document));
            notebook->addNote(ressource);
        }
    }
    else{
        parentLayout = new QVBoxLayout();
        EditorPage->setLayout(parentLayout);
    }
    nm = &NotesManager::getInstance();
    try{
        ressource = &nm->getNewNote(nt);
        noteEditor = ressource->createEditor();
        parentLayout->addWidget(noteEditor);
        if(notebook)
            notebook->addNote(ressource);
    }
    catch(NotesException e){
        QMessageBox::critical(this, "Error", e.getInfo());
    }
}


void MainWindow::UI_OPEN_FILE(){

    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Notes (*.art *.img *.vid *.aud *.doc)");
    QLayout *parentLayout;

    if(!fichier.isNull()){
        if(EditorPage->layout()){
            parentLayout = EditorPage->layout();
            if(notebook == 0){
                // there is already one ressource, create a doc to envelope it.
                notebook = static_cast<Document*>(&nm->getNewNote(document));
                // ressource here is the first note for the first editor.
                notebook->addNote(ressource);
            }
        }
        else{
            // First time, no layout yet.
            parentLayout = new QVBoxLayout();
            EditorPage->setLayout(parentLayout);
        }
        nm = &NotesManager::getInstance();
        try{
            ressource = &nm->getNote(fichier);
            noteEditor = ressource->createEditor();
            parentLayout->addWidget(noteEditor);
            if(notebook)
                notebook->addNote(ressource);
        }
        catch(NotesException e){
            QMessageBox::critical(this, "Error", e.getInfo());
        }
    }
}

void MainWindow::UI_TAB_CHANGE_HANDLER(int n){
    switch(n){
    case -1:{
        return;
    }
    case 1:{
        qDebug()<<"HTML";
        this->noteEditor->BACKEND_SET();
        Note * toConvert = notebook ? notebook : ressource;
        QString HTML = toConvert->exportNote(NotesManager::getInstance().strategies->value(html));
        qDebug()<<HTML;
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
        this->noteEditor->BACKEND_SET();
        Note * toConvert = notebook ? notebook : ressource;
        QString TEX = toConvert->exportNote(NotesManager::getInstance().strategies->value(tex));
        if(texViewerPage->layout()){
            delete tv;
            delete texViewerPage->layout();
        }

        // add tex viewer into tab
        tv = new TexViewer(TEX);
        QVBoxLayout *parentLayoutTV = new QVBoxLayout();
        parentLayoutTV->addWidget(tv);
        texViewerPage->setLayout(parentLayoutTV);
        break;
    }
    case 3:{
        qDebug()<<"Text";
        this->noteEditor->BACKEND_SET();
        Note * toConvert = notebook ? notebook : ressource;
        QString TEX = toConvert->exportNote(NotesManager::getInstance().strategies->value(text));
        if(textViewerPage->layout()){
            delete textv;
            delete textViewerPage->layout();
        }

        // add tex viewer into tab
        textv = new TextViewer(TEX);
        QVBoxLayout *parentLayoutTextV = new QVBoxLayout();
        parentLayoutTextV->addWidget(textv);
        textViewerPage->setLayout(parentLayoutTextV);
        break;
    }
    default:
        return;
    }
}
