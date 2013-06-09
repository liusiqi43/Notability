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
#include "trashDialog.h"
#include <typeinfo>
#include <QMap>
#include <QScrollArea>
#include "ui_mainwindow.h"
#include <QSettings>
#include <QStandardPaths>
#include <QCoreApplication>
#include <assert.h>
#include "TreeItem.h"
#include <QCheckBox>
#include "TagManager.h"
#include <QStandardItem>
#include "Filter.h"
#include "Binary.h"
#include <QDebug>
#include <QProcess>
#include "ListWidgetItemCheckTag.h"
#include "UndoableActions.h"

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

void MainWindow::createUndoView()
{
    undoView = new QUndoView(undoStack);
    undoView->setWindowTitle(tr("Command List"));
    undoView->setAttribute(Qt::WA_QuitOnClose, false);
}

void MainWindow::layingOutStuff(){

    tab = new QTabWidget();
    EditorPage = new QWidget();
    htmlViewerPage = new QWidget();
    texViewerPage = new QWidget();
    textViewerPage = new QWidget();


    editorWidget = new QWidget;
    ui->editorScroll->setWidget(editorWidget);
    tab->addTab(EditorPage, "Editor");
    tab->addTab(htmlViewerPage, "HTML");
    tab->addTab(texViewerPage, "TeX");
    tab->addTab(textViewerPage, "Text");
    tab->setTabIcon(0,QIcon(":images/edit"));
    tab->setTabIcon(1,QIcon(":images/html"));
    tab->setTabIcon(2,QIcon(":images/tex"));
    tab->setTabIcon(3,QIcon(":images/text"));

    layout = new QVBoxLayout();
    layout->addWidget(tab);

    editorWidget->setLayout(layout);


    QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(BACKEND_CLOSING()));

    QObject::connect(ui->noteBookTree, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(UI_LOAD_FROM_SIDE_BAR(const QModelIndex&)));
    QObject::connect(ui->tagList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(CHANGE_NAME_TAG_OR_STOCK_DISABLED_TAGS(QListWidgetItem*)));
    // Tab change handling
    QObject::connect(tab, SIGNAL(currentChanged(int)), this, SLOT(UI_TAB_CHANGE_HANDLER(int)));

    QObject::connect(ui->searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateSideBarWithNewSearchFilter(QString)));

}

void MainWindow::preparingUndoableCommands()
{
    undoStack = new QUndoStack(this);
    undoAction = undoStack->createUndoAction(this, tr("&Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);

    redoAction = undoStack->createRedoAction(this, tr("&Redo"));
    redoAction->setShortcuts(QKeySequence::Redo);

    historyBtn = new QAction("History", this);
    createUndoView();

    // Undo redo
    QObject::connect(historyBtn, SIGNAL(triggered()), undoView, SLOT(show()));
    QObject::connect(redoAction, SIGNAL(triggered()), QApplication::activeWindow(), SLOT());
    QObject::connect(undoAction, SIGNAL(triggered()), QApplication::activeWindow(), SLOT());
}

void MainWindow::createActions(){
    QToolBar *toolBar = addToolBar("General");
    QAction *actionQuit = new QAction("&Quit", this);

    actionQuit->setIcon(QIcon(":images/quit"));

    QAction *actionTrashBin = new QAction("&Trash", this);
    actionTrashBin->setIcon(QIcon(":images/trash"));

    QAction *actionSaveAll = new QAction("&Save all", this);
    actionSaveAll->setIcon(QIcon(":images/saveAll"));

    // subclassed QAction, this emets also the NoteType. So that we don't need different handling slot
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
    QMenu *menuNew = new QMenu("&New...");
    menuNew->addAction(actionNewArticle);
    menuNew->addAction(actionNewImageNote);
    menuNew->addAction(actionNewVideoNote);
    menuNew->addAction(actionNewAudioNote);
    menuNew->addAction(actionNewDocument);

    // subclassed QAction, this emets also the ExportType
    ExportTypeSignalAction *actionExportHTML = new ExportTypeSignalAction(html, "&HTML", this);
    ExportTypeSignalAction *actionExportTeX = new ExportTypeSignalAction(tex, "&TeX", this);
    ExportTypeSignalAction *actionExportText = new ExportTypeSignalAction(text, "&Text", this);

    QMenu *menuExport = new QMenu("&Export");
    menuExport->addAction(actionExportHTML);
    menuExport->addAction(actionExportTeX);
    menuExport->addAction(actionExportText);
    actionExportHTML->setIcon(QIcon(":images/html"));
    actionExportTeX->setIcon(QIcon(":images/tex"));
    actionExportText->setIcon(QIcon(":images/text"));
    menuFichier = menuBar()->addMenu("&File");
    menuEdition = menuBar()->addMenu("&Edit");

    menuFichier->addMenu(menuNew);
    menuFichier->addMenu(menuExport);

    menuFichier->addAction(actionQuit);

    QAction *changeWorkSpaceAction = new QAction("Change workspace", this);
    menuEdition->addAction(changeWorkSpaceAction);

    toolBar->addAction(actionNewArticle);
    toolBar->addAction(actionNewImageNote);
    toolBar->addAction(actionNewVideoNote);
    toolBar->addAction(actionNewAudioNote);
    toolBar->addSeparator();
    toolBar->addAction(actionNewDocument);
    toolBar->addAction(actionSaveAll);
    toolBar->addSeparator();
    toolBar->addAction(undoAction);
    undoAction->setIcon(QIcon(":images/undo"));
    toolBar->addAction(redoAction);
    redoAction->setIcon(QIcon(":images/redo"));
    toolBar->addAction(historyBtn);
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(spacer);
    toolBar->addAction(actionTrashBin);
    toolBar->addAction(actionQuit);

    QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionNewArticle, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewDocument, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewImageNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewAudioNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));
    QObject::connect(actionNewVideoNote, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_NEW_NOTE_EDITOR(const int)));

    QObject::connect(actionExportHTML, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_EXPOR_TO_FILE(const int)));
    QObject::connect(actionExportTeX, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_EXPOR_TO_FILE(const int)));
    QObject::connect(actionExportText, SIGNAL(triggeredWithId(const int)), this, SLOT(UI_EXPOR_TO_FILE(const int)));

    QObject::connect(changeWorkSpaceAction, SIGNAL(triggered()), this, SLOT(CHANGE_NEW_WORKSPACE()));

    QObject::connect(ui->addTag, SIGNAL(clicked()), this, SLOT(ADD_TAG()));
    QObject::connect(ui->removeTag, SIGNAL(clicked()), this, SLOT(REMOVE_TAG()));
    QObject::connect(actionTrashBin, SIGNAL(triggered()), this, SLOT(FIRE_UP_TRASH_BIN_DIALOG()));

    QObject::connect(actionSaveAll, SIGNAL(triggered()), this, SLOT(BACKEND_CLOSING()));


}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), hv(0), tv(0), nm(0), textv(0), tm(0), sideBarModel(0)
{
    ui->setupUi(this);

    // Creat a new article, with generated file path and empty title&text
    nm = &NotesManager::getInstance();
    tm = &TagManager::getInstance();

    layingOutStuff();
    preparingUndoableCommands();
    createActions();

    updateSideBar();
    createTagList();
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
    try{
        nt = static_cast<NoteType>(type);
    }catch(std::bad_cast& bc){
        QMessageBox::critical(this, "Error", "something serious happenned during creation of new editor..."+QString(bc.what()));
    }
    if(nt!=document){

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

        ressources.clear();
        openedFiles.clear();

        try{
            Note* temp = &nm->getNewNote(nt);
            Editor* noteEditor = temp->createAndAttachEditor();
            QLayout * layout = EditorPage->layout() ? EditorPage->layout() : new QVBoxLayout();
            layout->addWidget(noteEditor);
            if(!EditorPage->layout())
                EditorPage->setLayout(layout);
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

    ressources.clear();
    openedFiles.clear();

    Editor *editor = temp->getItemId()->createAndAttachEditor();
    // TODO Deep
    editor->updateDocBtnWithRessource(temp);

    QLayout * layout = EditorPage->layout() ? EditorPage->layout() : new QVBoxLayout();
    layout->addWidget(editor);
    if(!EditorPage->layout())
        EditorPage->setLayout(layout);
}

void MainWindow::LoadExportToViewerPage(ExportType type, QList<Note*>& list, QWidget* viewerPage, Viewer* viewer){
    if(list.isEmpty()){
        QMessageBox::warning(0, "No opened file", "You need to open some notes in order to export.");
        return;
    }
    ExportStrategy *es = NotesManager::getInstance().strategies->value(type);
    QString content("");

    for(QList<Note*>::iterator it = list.begin(); it != list.end(); ++it){
        (*it)->getEditor()->BACKEND_SET();
        //        content+=(*it)->exportNote(es);
    }
    QList<Note*>::iterator it = list.begin();
    content = (*it)->exportNote(es);

    if(viewerPage){
        // export to viewer.
        QLayout* parentLayout = viewerPage->layout();

        delete viewer;
        if(parentLayout)
            delete parentLayout;

        // add viewer into tab
        parentLayout = new QVBoxLayout();

        switch(type){
        case html:
            viewer = new HtmlViewer(content);
            //            qDebug()<<content;
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
    } else {
        // Used to export to file
        // now that content is prepared, we need a file path to save.
        QString defaultFilename = (*it)->getTitle();
        switch(type){
        case html:
            defaultFilename+=".html";
            break;
        case tex:
            defaultFilename+=".tex";
            break;
        case text:
            defaultFilename+=".txt";
            break;
        default:
            throw NotesException("Should not happen.");
        }

        qDebug()<<QStandardPaths::locate(QStandardPaths::DocumentsLocation, "", QStandardPaths::LocateDirectory)+defaultFilename;

        QString filename = QFileDialog::getSaveFileName(this, "Export to...", QStandardPaths::locate(QStandardPaths::DocumentsLocation, "", QStandardPaths::LocateDirectory)+defaultFilename);
        if(!filename.isEmpty()){

            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
                throw NotesException("Failed to save your note, please check if I have the permission to write on your harddisk and stop hacking the software!");

            QTextStream flux(&f);
            flux<<content;
            f.close();
        }
    }
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
//        QMessageBox msgBox;
//        msgBox.setText("Unsaved modifications");
//        msgBox.setInformativeText("You have unsaved modifications, do you want to save them?");
//        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
//        msgBox.setDefaultButton(QMessageBox::No);
//        int ret = msgBox.exec();

//        switch(ret){
//        case QMessageBox::Yes:{
            try{
                nm->saveNote(*nm->getRootDocument());
                QSettings settings;
                if(!settings.value("workspaceChanged").toBool()){
                    settings.setValue("rootDocument", nm->getRootDocument()->getFilePath());
                    settings.setValue(settings.value("workspace").toString(), nm->getRootDocument()->getFilePath());
                    settings.sync();
                }
            }
            catch (NotesException e){
                QMessageBox::warning(this, "Saving error", e.getInfo());
            }
//            break;
//        }
//        case QMessageBox::No: {
//            break;
//        }
//        default:{}
//        }
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

void MainWindow::createTagList()
{
    tm = &TagManager::getInstance();

    for(tagSetIt it = tm->begin(); it != tm->end(); it++)
    {
        qDebug() << (*it)->getName();
        ListWidgetItemCheckTag* item = new ListWidgetItemCheckTag((*it)->getName(), (*it), ui->tagList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable); // set checkable flag
        item->setCheckState(Qt::Checked);
    }
}

void MainWindow::updateSideBarWithNewSearchFilter(QString str)
{
    FilterKit* kit = FilterKit::getInstance();
    SearchFilter* filter = SearchFilter::getInstance();
    filter->setEnabledTitleContaining(str);
    kit->setFilter(search, filter);
    updateSideBar();
}


void MainWindow::UI_EXPOR_TO_FILE(const int type)
{
    ExportType et = static_cast<ExportType>(type);
    LoadExportToViewerPage(et, ressources);
}

void MainWindow::addRessources(Note* n)
{
    ressources.append(n);

}

void MainWindow::CHANGE_NEW_WORKSPACE()
{
    QFileDialog *dialog = new QFileDialog(this, "Switch to new workspace");
    dialog->setFileMode(QFileDialog::Directory);
    dialog->show();
    if (dialog->exec()){
        QSettings settings;
        QString fileNames = dialog->selectedFiles().first();
        if(settings.contains(fileNames)){
            // Need to restore old workspace.
            settings.setValue("rootDocument", settings.value(fileNames));
            QMessageBox::information(this, "Restarting application", "We have detected your old notes stored in the new workspace, we will restart your application and restore them for you... Behold!");
            QProcess::startDetached(QApplication::applicationFilePath());
            exit(12);
        } else {
            // Ask if I should copy old notes or start from scratch
            QMessageBox msgBox;
            msgBox.setText("Do you want to copy your notes to new workspace?");
            msgBox.setInformativeText("Otherwise you will have a fresh new workspace. Either way, we will restart the application, your modifications will be saved.");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::No);
            int ret = msgBox.exec();

            switch (ret)  {
            case QMessageBox::Yes:{
                qDebug()<<"You clicked on yes";
                settings.setValue("workspaceChanged", true);
                settings.setValue("workspace", fileNames);
                // New workspace, we copy all notes or start from scratch
                Document * oldRoot = nm->getRootDocument();
                Document * newRoot = dynamic_cast<Document*>(NotesManager::getInstance().factories->value(document)->buildNewNote());
                newRoot->setTitle("~");

                nm->setRootDocument(newRoot);
                for(nListIt it = oldRoot->begin(); it!=oldRoot->end(); ++it){
                    //                    if(!explored.contains(*it)){
                    qDebug() << "Copyinig" << (*it)->getTitle();
                    nm->getNoteClone(**it);
                    //                        explored << *it;
                    //                    }
                    qDebug()<<"survived######";
                }
                settings.setValue("rootDocument", newRoot->getFilePath());
                // Stock new workspace and the corresponding rootdoc path
                settings.setValue(fileNames, newRoot->getFilePath());
                settings.sync();
                this->BACKEND_CLOSING();
//                NotesManager::libererInstance();
                QProcess::startDetached(QApplication::applicationFilePath());
                exit(12);
                break;
            }
            case QMessageBox::No:{
                settings.setValue("workspaceChanged", true);
                settings.setValue("workspace", fileNames);
                settings.setValue("rootDocument", QString());
                settings.sync();
                this->BACKEND_CLOSING();
                NotesManager::libererInstance();
                QProcess::startDetached(QApplication::applicationFilePath());
                exit(12);
                // Don't Save was clicked
                break;
            }
            case QMessageBox::Cancel:
                // Cancel was clicked
                break;
            default:
                // should never be reached
                break;
            }
        }
    }
}

void MainWindow::FIRE_UP_TRASH_BIN_DIALOG()
{
    new TrashDialog();
}

void MainWindow::ADD_TAG()
{
    if(ui->tagList->findItems("New Tag", Qt::MatchExactly).count()==0)
    {
        undoStack->push(new AddNewTagCmd(ui->tagList));
    }
    else QMessageBox::information(this, "Erreur", "Nouveau Tag déjà existant...");
}

void MainWindow::REMOVE_TAG()
{
    //    qDebug() << "Got current item to delete: " << ui->tagList->currentItem()->data(0).toString();
    if(ui->tagList->currentItem())
    {
        undoStack->push(new RemoveCurrentTagCmd(ui->tagList, dynamic_cast<ListWidgetItemCheckTag *>(ui->tagList->currentItem())));
    }

}

void MainWindow::CHANGE_NAME_TAG_OR_STOCK_DISABLED_TAGS(QListWidgetItem* item)
{
    if(item->data(0).toString() != "New Tag"){
        TagFilter *f = TagFilter::getInstance();
        Tag* t = static_cast<ListWidgetItemCheckTag *>(item)->getTag();
        if(t && item->checkState()==Qt::Checked)
        {
            if(f->contains(t))
                f->removeDisabledTag(t);
        }
        else
            if(t)
                f->addDisabledTag(t);

        FilterKit* kit = FilterKit::getInstance();
        kit->setFilter(tag, f);
        updateSideBar();

        ListWidgetItemCheckTag* tagItem = dynamic_cast<ListWidgetItemCheckTag *>(item);
        if(item->data(0).toString() != tagItem->getTag()->getName())
            undoStack->push(new EditCurrentTagCmd(tagItem, ui->tagList, 0));
    }
}
