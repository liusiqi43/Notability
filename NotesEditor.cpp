#include "NotesEditor.h"
#include "ArticleEditor.h"

void NotesEditor::UI_INFORM_NOT_IMPLEMENTED(){
    QMessageBox::information(this, "New fonctionality", "To be implemented...");
}

void NotesEditor::UI_OPEN_FILE(){
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Documents (*.txt)");
    nm = &NotesManager::getInstance();
    Article &art = nm->getArticle(fichier);
    ArticleEditor * articleEditor = new ArticleEditor(&art, articleEditorPage);
    articleEditor->show();
}

NotesEditor::NotesEditor(QWidget *parent) :
    QMainWindow(parent)
{
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

    onglets = new QTabWidget(this);
    onglets->setGeometry(30, 20, 500, 700);

    articleEditorPage = new QWidget;

    onglets->addTab(articleEditorPage, "Editor");

    QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionOpenArticle, SIGNAL(triggered()), this, SLOT(UI_OPEN_FILE()));
    QObject::connect(actionOpenImage, SIGNAL(triggered()), this, SLOT(UI_INFORM_NOT_IMPLEMENTED()));
}
