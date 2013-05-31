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
#include "TreeItem.h"

MainWindow* MainWindow::instance = 0;

MainWindow* MainWindow::getInstance(){
    if(!instance){
        instance = new MainWindow();
    }
    return instance;
}

void MainWindow::freeInstance()
{
    if(instance){
        delete instance;
        instance = 0;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), hv(0), tv(0), textv(0), nm(0), sideBarModel(0)
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



    QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionOpen, SIGNAL(triggered()), this, SLOT(UI_OPEN_FILE()));
    QObject::connect(actionNewArticle, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewDocument, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewImageNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewAudioNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewVideoNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));

    QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(BACKEND_CLOSING()));

    QObject::connect(ui->noteBookTree, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(UI_LOAD_FROM_SIDE_BAR(const QModelIndex&)));

    // Tab change handling
    QObject::connect(tab, SIGNAL(currentChanged(int)), this, SLOT(UI_TAB_CHANGE_HANDLER(int)));
    updateSideBar();
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
    if(nt!=document){

        parentLayout = EditorPage->layout() ? EditorPage->layout() : new QVBoxLayout();
        try{
            Note* temp = &nm->getNewNote(nt);
            ressources << temp;

            Editor* noteEditor = temp->createAndAttachEditor();
            parentLayout->addWidget(noteEditor);
            if(!EditorPage->layout())
                EditorPage->setLayout(parentLayout);
            openedFiles << temp->getFilePath();
        }
        catch(NotesException e){
            QMessageBox::critical(this, "Error", e.getInfo());
        }
    }
    else {
        &nm->getNewNote(nt);
        updateSideBar();
    }
}

void MainWindow::UI_LOAD_FROM_SIDE_BAR(const QModelIndex& index){
    TreeItem * temp = sideBarModel->getItem(index);
    if(openedFiles.contains(temp->getItemId()->getFilePath()))
        return;
    Editor *editor = temp->getItemId()->createAndAttachEditor();

    for(QList<Note*>::iterator it = ressources.begin(); it != ressources.end(); ++it){
        (*it)->getEditor()->BACKEND_SET();
        delete (*it)->getEditor();
    }
    delete EditorPage->layout();

    ressources.clear();
    openedFiles.clear();

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(editor);
    EditorPage->setLayout(layout);

    openedFiles << temp->getItemId()->getFilePath();
    ressources << temp->getItemId();
}


void MainWindow::UI_OPEN_FILE(){
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Notes (*.art *.img *.vid *.aud *.doc)");

    QLayout *parentLayout;
    if(!fichier.isNull()){
        // Test if already opened
        if(openedFiles.contains(fichier))
            return;

        parentLayout = EditorPage->layout() ? EditorPage->layout() : new QVBoxLayout();
        try{
            Note* temp = &nm->getNote(fichier);
            ressources << temp;

            Editor* noteEditor = temp->createAndAttachEditor();
            parentLayout->addWidget(noteEditor);
            if(!EditorPage->layout())
                EditorPage->setLayout(parentLayout);
            openedFiles << temp->getFilePath();
        }
        catch(NotesException e){
            QMessageBox::critical(this, "Error", e.getInfo());
        }
    }
    updateSideBar();
}

void MainWindow::LoadExportToViewerPage(ExportType type, QList<Note*>& list, QWidget* viewerPage, Viewer* viewer){
    ExportStrategy *es = NotesManager::getInstance().strategies->value(type);
    QString content("");

    for(QList<Note*>::iterator it = list.begin(); it != list.end(); ++it){
        (*it)->getEditor()->BACKEND_SET();
        content+=(*it)->exportNote(es);
    }

    QLayout* parentLayout = viewerPage->layout() ? viewerPage->layout() : new QVBoxLayout();

    delete viewer;
    delete parentLayout;

    // add viewer into tab
    parentLayout = new QVBoxLayout();
    switch(type){
    case html:
        viewer = new HtmlViewer(content);
        break;
    case tex:
        viewer = new TexViewer(content);
        break;
    case text:
        viewer = new TextViewer(content);
        break;
    default:
        throw NotesException("Error... should not happen. Handling tab action");
    }
    parentLayout->addWidget(viewer);
    viewerPage->setLayout(parentLayout);
}

void MainWindow::UI_TAB_CHANGE_HANDLER(int n){
    if(!ressources.empty()){
        switch(n){
        case -1:{
            return;
        case 1:{
                qDebug()<<"HTML";
                LoadExportToViewerPage(html, ressources, htmlViewerPage, hv);
                break;
            }
            case 2:{
                qDebug()<<"TeX";
                LoadExportToViewerPage(tex, ressources, texViewerPage, tv);
                break;
            }
            case 3:{
                qDebug()<<"Text";
                LoadExportToViewerPage(text, ressources, textViewerPage, textv);
                break;
            }
            default:
                return;
            }
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

void MainWindow::updateSideBar()
{
    TreeModel *old = 0;
    if(sideBarModel)
        old = sideBarModel;
    sideBarModel = new TreeModel();
    ui->noteBookTree->setModel(sideBarModel);
    delete old;
    old = 0;
}
