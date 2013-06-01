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

void MainWindow::addOpenedFiles(const QString & path)
{
    openedFiles.insert(path);
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
//    menuFichier->addAction(actionOpen);

    menuFichier->addAction(actionQuit);

//    toolBar->addAction(actionOpen);
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



//    QStandardItemModel* model = new QStandardItemModel; // 3 rows, 1 col
//    QStandardItem* Item = new QStandardItem;
//    QStandardItem* Item2 = new QStandardItem;

//    Item->setText("test");
//    Item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
//    Item->setData(Qt::Checked, Qt::CheckStateRole);


//    Item2 = new QStandardItem;
//      Item2->setText("test2");
//      Item2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
//      Item2->setData(Qt::Unchecked, Qt::CheckStateRole);


//      QObject::connect(model, SIGNAL(dataChanged ( const QModelIndex&, const QModelIndex&)), this, SLOT(slot_changed(const QModelIndex&, const QModelIndex&)));
//    model->insertRow(0, Item);
//    model->insertRow(1, Item2);
//    Items = new std::vector<QStandardItem*>();
//    Items->push_back(Item);
//    Items->push_back(Item2);

//    ui->comboBox->setModel(model);


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
        for(QList<Note*>::iterator it = ressources.begin(); it != ressources.end(); ++it){
            if((*it)->getEditor()){
                (*it)->getEditor()->BACKEND_SET();
                delete (*it)->getEditor();
                (*it)->setEditor(0);
            }
        }
//        delete EditorPage->layout();
        parentLayout = EditorPage->layout() ? EditorPage->layout() : new QVBoxLayout();
        try{
            Note* temp = &nm->getNewNote(nt);
//            ressources << temp;
            ressources.clear();
            openedFiles.clear();

            Editor* noteEditor = temp->createAndAttachEditor();
            parentLayout->addWidget(noteEditor);
            if(!EditorPage->layout())
                EditorPage->setLayout(parentLayout);
//            openedFiles << temp->getFilePath();
        }
        catch(NotesException e){
            QMessageBox::critical(this, "Error", e.getInfo());
        }
    }
    else {
        &nm->getNewNote(nt);
    }
    updateSideBar();
}

void MainWindow::UI_LOAD_FROM_SIDE_BAR(const QModelIndex& index){
    TreeItem * temp = sideBarModel->getItem(index);

//    if(openedFiles.contains(temp->getItemId()->getFilePath()))
//        return;

    bool first = false;
    for(QList<Note*>::iterator it = ressources.begin(); it != ressources.end(); ++it){
        if(first) break;
        if((*it)->getEditor()){
            qDebug()<<(*it)->getTitle();
            (*it)->getEditor()->BACKEND_SET();
            delete (*it)->getEditor();
            (*it)->setEditor(0);
            first = true;
        }
    }
//    delete EditorPage->layout();

    ressources.clear();
    openedFiles.clear();

    Editor *editor = temp->getItemId()->createAndAttachEditor();
    // TODO Deep
    editor->updateDocBtnWithRessource(temp);

    QLayout * layout = EditorPage->layout() ? EditorPage->layout() : new QVBoxLayout();
    layout->addWidget(editor);
    if(!EditorPage->layout())
        EditorPage->setLayout(layout);

//    if(temp->getItemId()->isDocument()){
//        Document *doc = static_cast<Document*>(temp->getItemId());
////        qDebug()<<"last:"<<doc->last()->getTitle();
////        for(Document::DepthFirstIterator it = doc->beginDFIterator(); !it.isDone(); ++it){
////            qDebug()<<(*it)->getTitle();
////            openedFiles << (*it)->getFilePath();
////            ressources << (*it);
////        }

//    }
//    else{
//        openedFiles << temp->getItemId()->getFilePath();
//        ressources << temp->getItemId();
//    }
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
//        content+=(*it)->exportNote(es);
    }
    QList<Note*>::iterator it = list.begin();
    content = (*it)->exportNote(es);

    QLayout* parentLayout = viewerPage->layout() ? viewerPage->layout() : new QVBoxLayout();

    delete viewer;
    delete parentLayout;

    // add viewer into tab
    parentLayout = new QVBoxLayout();
    switch(type){
    case html:
        viewer = new HtmlViewer(content);
        qDebug()<<content;
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

//void MainWindow::UI_UPDATE_TITLE_WIDGET(const QModelIndex& index, const QModelIndex& index2)
//{
//    qDebug()<<"called here!";
//    TreeItem * temp = sideBarModel->getItem(index);
//    if(temp->getItemId()->getEditor()){
//        temp->getItemId()->getEditor()->setTitleWidgetText(temp->data(0).toString());
//    }
//}



void MainWindow::slot_changed(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
  //std::cout << "topLeft: " << topLeft.row() << std::endl;
  //std::cout << "bottomRight: " << bottomRight.row() << std::endl;
  std::cout << "Item " << topLeft.row() << " " << std::endl;
  QStandardItem* item = (*this->Items)[topLeft.row()];
  if(item->checkState() == Qt::Unchecked)
    {
    std::cout << "Unchecked!" << std::endl;
    }
  else if(item->checkState() == Qt::Checked)
    {
    std::cout << "Checked!" << std::endl;
    }

}

void MainWindow::addRessources(Note* n)
{
    ressources.append(n);
}
