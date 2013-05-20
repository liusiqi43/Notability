#include "mainUI.h"

void mainUI::UI_INFORM_NOT_IMPLEMENTED(){
    QMessageBox::information(this, "New fonctionality", "To be implemented...");
}

void mainUI::UI_OPEN_FILE(){

    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Documents (*.txt)");

    if(!fichier.isNull()){
        if(EditorPage->layout()){
            delete noteEditor;
            delete EditorPage->layout();
        }

        nm = &NotesManager::getInstance();
        ressource = &nm->getArticle(fichier);
        noteEditor = ressource->createEditor();

        QVBoxLayout *parentLayout = new QVBoxLayout();
        EditorPage->setLayout(parentLayout);
        parentLayout->addWidget(noteEditor);
    }
}

void mainUI::UI_OPEN_IMAGENOTE(){

    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Image Notes (*.img)");

    if(!fichier.isNull()){
        if(EditorPage->layout()){
            delete noteEditor;
            delete EditorPage->layout();
        }

        nm = &NotesManager::getInstance();
        ressource = &nm->getImageNote(fichier);
        noteEditor = ressource->createEditor();

        QVBoxLayout *parentLayout = new QVBoxLayout();
        EditorPage->setLayout(parentLayout);
        parentLayout->addWidget(noteEditor);
    }
}

void mainUI::UI_TAB_CHANGE_HANDLER(int n){
    switch(n){
    case -1:{
        return;
    }
    case 1:{
        qDebug()<<"HTML";
        qDebug()<<this->noteEditor->toHtml();
        if(htmlViewerPage->layout()){
            delete hv;
            delete htmlViewerPage->layout();
        }

        // add html viewer into tab
        hv = new HtmlViewer(this->noteEditor->toHtml());
        QVBoxLayout *parentLayoutHV = new QVBoxLayout();
        parentLayoutHV->addWidget(hv);
        htmlViewerPage->setLayout(parentLayoutHV);
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
    QAction *actionQuit = new QAction("&Quitter", this);
    QAction *actionOpenArticle = new QAction("&Article", this);
    QAction *actionOpenImage = new QAction("&Image", this);
    QAction *actionOpenVideo = new QAction("&Video", this);

    QMenu *menuOuvrir = new QMenu("&Ouvrir");

    menuFichier = menuBar()->addMenu("&Fichier");
    menuEdition = menuBar()->addMenu("&Edition");

    menuFichier->addMenu(menuOuvrir);

    menuFichier->addAction(actionQuit);
    menuOuvrir->addAction(actionOpenArticle);
    menuOuvrir->addAction(actionOpenImage);
    menuOuvrir->addAction(actionOpenVideo);
    toolBar->addAction(actionOpenArticle);
    toolBar->addAction(actionOpenImage);
    toolBar->addAction(actionOpenVideo);
    toolBar->addAction(actionQuit);

    tab = new QTabWidget();
    EditorPage = new QWidget();
    htmlViewerPage = new QWidget();

    // Creat a new article, with generated file path and empty title&text
    // TODO add article to a default document.
    nm = &NotesManager::getInstance();
//    ressource = &nm->getNewArticle();
    ressource = &nm->getNewImageNote();

    // add default article editor into layout
    QVBoxLayout *parentLayout = new QVBoxLayout();
    EditorPage->setLayout(parentLayout);
    noteEditor = ressource->createEditor();
//    noteEditor = new ArticleEditor(dynamic_cast<Article *>(ressource));
    parentLayout->addWidget(noteEditor);

    tab->addTab(EditorPage, "Editor");
    tab->addTab(htmlViewerPage, "HTML");

    layout = new QVBoxLayout();
    layout->addWidget(tab);

    mainWidget->setLayout(layout);

    this->setCentralWidget(mainWidget);
    qDebug()<<"Hello";
    QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionOpenArticle, SIGNAL(triggered()), this, SLOT(UI_OPEN_FILE()));
    QObject::connect(actionOpenImage, SIGNAL(triggered()), this, SLOT(UI_OPEN_IMAGENOTE()));
    QObject::connect(actionOpenVideo, SIGNAL(triggered()), this, SLOT(UI_INFORM_NOT_IMPLEMENTED()));

    // Tab change handling
    QObject::connect(tab, SIGNAL(currentChanged(int)), this, SLOT(UI_TAB_CHANGE_HANDLER(int)));
}
