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
#include <QSettings>
#include <QCoreApplication>
#include <assert.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ressource = 0;
    editorWidget = new QWidget;
    noteEditors = new QList<Editor*>;
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
    toolBar->addAction(actionNewArticle);
    toolBar->addAction(actionNewImageNote);
    toolBar->addAction(actionNewVideoNote);
    toolBar->addAction(actionNewAudioNote);
    toolBar->addAction(actionNewDocument);
    toolBar->addAction(actionQuit);

    tab = new QTabWidget();
    EditorPage = new QWidget();
    htmlViewerPage = new QWidget();
    texViewerPage = new QWidget();
    textViewerPage = new QWidget();

    // Creat a new article, with generated file path and empty title&text
    nm = &NotesManager::getInstance();

    tab->addTab(EditorPage, "Editor");
    tab->addTab(htmlViewerPage, "HTML");
    tab->addTab(texViewerPage, "TeX");
    tab->addTab(textViewerPage, "Text");

    layout = new QVBoxLayout();
    layout->addWidget(tab);

    editorWidget->setLayout(layout);

    ui->noteBookTree->setModel(new TreeModel());

    QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionOpen, SIGNAL(triggered()), this, SLOT(UI_OPEN_FILE()));
    QObject::connect(actionNewArticle, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewDocument, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewImageNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewAudioNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewVideoNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));

    QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(BACKEND_CLOSING()));

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
        if(ressource != 0 && !ressource->isDocument()){
            Note *temp = ressource;
            // Remove it because it will be added to a subDocument of rootDocument
            nm->removeNote(ressource);
            // there is already one ressource, create a doc to envelope it.
            ressource = &nm->getNewNote(document);
            // ressource here is the first note for the first editor.
            ressource->addNote(temp);
        }
    }
    else{
        // First time, no layout yet.
        parentLayout = new QVBoxLayout();
        EditorPage->setLayout(parentLayout);
    }
    try{
        Note *temp = &nm->getNewNote(nt);

        if(ressource == 0)
            ressource = temp;
        else{
            // Remove it because it will be added to a subDocument of rootDocument
            nm->removeNote(temp);
            ressource->addNote(temp);
        }

        Editor* noteEditor = temp->createEditor();
        parentLayout->addWidget(noteEditor);
        noteEditors->append(noteEditor);

        openedFiles << temp->getFilePath();
    }
    catch(NotesException e){
        QMessageBox::critical(this, "Error", e.getInfo());
    }
}


void MainWindow::UI_OPEN_FILE(){
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Notes (*.art *.img *.vid *.aud *.doc)");

    QLayout *parentLayout;
    if(!fichier.isNull()){
        // Test if already opened
        if(openedFiles.contains(fichier))
            return;

        if(EditorPage->layout()){
            parentLayout = EditorPage->layout();
            if(ressource != 0 && !ressource->isDocument()){
                Note *temp = ressource;
                // Remove it because it will be added to a subDocument of rootDocument
                nm->removeNote(ressource);
                // there is already one ressource, create a doc to envelope it.
                ressource = &nm->getNewNote(document);
                // ressource here is the first note for the first editor.
                ressource->addNote(temp);
            }
        }
        else{
            // First time, no layout yet.
            parentLayout = new QVBoxLayout();
            EditorPage->setLayout(parentLayout);
        }
        try{
            Note *temp = &nm->getNote(fichier);

            if(ressource == 0)
                ressource = temp;
            else{
                // Remove it because it will be added to a subDocument of rootDocument
                nm->removeNote(temp);
                ressource->addNote(temp);
            }

            Editor* noteEditor = temp->createEditor();
            parentLayout->addWidget(noteEditor);
            noteEditors->append(noteEditor);

            openedFiles << fichier;
        }
        catch(NotesException e){
            QMessageBox::critical(this, "Error", e.getInfo());
        }
    }
}

void MainWindow::UI_TAB_CHANGE_HANDLER(int n){
    ui->noteBookTree->setModel(new TreeModel());
    if(ressource){
        switch(n){
        case -1:{
            return;
        }
        case 1:{
            qDebug()<<"HTML";
            for(QList<Editor*>::iterator it = noteEditors->begin(); it != noteEditors->end(); ++it)
                (*it)->BACKEND_SET();

            // TODO one resource suffice
            QString HTML = ressource->exportNote(NotesManager::getInstance().strategies->value(html));
//            qDebug()<<HTML;
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
            for(QList<Editor*>::iterator it = noteEditors->begin(); it != noteEditors->end(); ++it)
                (*it)->BACKEND_SET();
            // TODO one resource suffice
            QString TEX = ressource->exportNote(NotesManager::getInstance().strategies->value(tex));
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
            for(QList<Editor*>::iterator it = noteEditors->begin(); it != noteEditors->end(); ++it)
                (*it)->BACKEND_SET();
            // TODO one resource suffice
            QString TEX = ressource->exportNote(NotesManager::getInstance().strategies->value(text));
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
}

void MainWindow::BACKEND_CLOSING()
{
    if(nm->getRootDocument()->isModified()){
        try{
            nm->saveNote(*nm->getRootDocument());
            QSettings settings;
            settings.setValue("rootDocument", nm->getRootDocument()->getFilePath());
            qDebug() << nm->getRootDocument()->getFilePath();
        }
        catch (NotesException e){
            QMessageBox::warning(this, "Saving error", e.getInfo());
        }
    }
}
