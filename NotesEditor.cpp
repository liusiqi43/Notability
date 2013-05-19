#include "NotesEditor.h"
#include "NotesManager.h"
#include "ArticleEditor.h"

void NotesEditor::UI_INFORM_NOT_IMPLEMENTED(){
    QMessageBox::information(this, "New fonctionality", "To be implemented...");
}

void NotesEditor::UI_OPEN_FILE(){

    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Documents (*.txt)");

    if(!fichier.isNull()){
        if(EditorPage->layout()){
            delete articleEditor;
            delete EditorPage->layout();
        }

        nm = &NotesManager::getInstance();
        ressource = &nm->getArticle(fichier);
        articleEditor = new ArticleEditor(ressource);

        QVBoxLayout *parentLayout = new QVBoxLayout();
        EditorPage->setLayout(parentLayout);
        parentLayout->addWidget(articleEditor);
    }
}

void NotesEditor::UI_TAB_CHANGE_HANDLER(int n){
    switch(n){
    case -1:{
        return;
    }
    case 1:{
        qDebug()<<"HTML";
        qDebug()<<"Current title: " << this->articleEditor->getTitleWidget()->text();
        qDebug()<<"Current text: " << this->articleEditor->getTextWidget()->toPlainText();
        if(htmlViewerPage->layout()){
            delete hv;
            delete htmlViewerPage->layout();
        }

        // add html viewer into tab
        hv = new HtmlViewer(new Article(
                                this->articleEditor->getTitleWidget()->text(),
                                this->articleEditor->getTextWidget()->toPlainText()
                                ));
        QVBoxLayout *parentLayoutHV = new QVBoxLayout();
        parentLayoutHV->addWidget(hv);
        htmlViewerPage->setLayout(parentLayoutHV);
        break;
    }
    default:
        return;
    }
}

NotesEditor::NotesEditor(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new QWidget;
    QToolBar *toolBar = addToolBar("General");
    QAction *actionQuit = new QAction("&Quitter", this);
    QAction *actionOpenArticle = new QAction("&Article", this);
    QAction *actionOpenImage = new QAction("&Image", this);

    QMenu *menuOuvrir = new QMenu("&Ouvrir");

    menuFichier = menuBar()->addMenu("&Fichier");
    menuEdition = menuBar()->addMenu("&Edition");

    menuFichier->addMenu(menuOuvrir);

    menuFichier->addAction(actionQuit);
    menuOuvrir->addAction(actionOpenArticle);
    menuOuvrir->addAction(actionOpenImage);
    toolBar->addAction(actionOpenArticle);
    toolBar->addAction(actionOpenImage);
    toolBar->addAction(actionQuit);

    tab = new QTabWidget();
    EditorPage = new QWidget();
    htmlViewerPage = new QWidget();

    // Creat a new article, with generated file path and empty title&text
    // TODO add article to a default document.
    nm = &NotesManager::getInstance();
    ressource = &nm->getNewArticle();

    // add default article editor into layout
    QVBoxLayout *parentLayout = new QVBoxLayout();
    EditorPage->setLayout(parentLayout);
    articleEditor = new ArticleEditor(ressource);
    parentLayout->addWidget(articleEditor);

    tab->addTab(EditorPage, "Editor");
    tab->addTab(htmlViewerPage, "HTML");

    layout = new QVBoxLayout();
    layout->addWidget(tab);

    mainWidget->setLayout(layout);

    this->setCentralWidget(mainWidget);

    QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionOpenArticle, SIGNAL(triggered()), this, SLOT(UI_OPEN_FILE()));
    QObject::connect(actionOpenImage, SIGNAL(triggered()), this, SLOT(UI_INFORM_NOT_IMPLEMENTED()));

    // Tab change handling
    QObject::connect(tab, SIGNAL(currentChanged(int)), this, SLOT(UI_TAB_CHANGE_HANDLER(int)));
}
