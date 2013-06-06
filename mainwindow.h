#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QObject>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QToolBar>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QListWidget>
#include "ExportStrategy.h"
#include "viewer.h"
#include <QStandardItem>

class Editor;
class HtmlViewer;
class TexViewer;
class TextViewer;
class Note;
class Document;
class TreeModel;
class NotesManager;
class TagManager;
class Tag;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainWindow(const MainWindow&);
    MainWindow& operator=(const MainWindow&);
    static MainWindow* instance;
    std::vector<QStandardItem*>* Items;
public:
    static MainWindow* getInstance();
    static void freeInstance();
    
    void addOpenedFiles(const QString&);
    void addRessources(Note *);
    void removeRessource(Note *n) {ressources.removeOne(n);}

signals:

public slots:
    void CHANGE_NEW_WORKSPACE();
    void UI_INFORM_NOT_IMPLEMENTED();
    void UI_NEW_NOTE_EDITOR(const int type);
    void UI_TAB_CHANGE_HANDLER(int);
    void BACKEND_CLOSING();
    void UI_LOAD_FROM_SIDE_BAR(const QModelIndex &index);
    void updateSideBar();
    void createTagList();
    void updateSideBarWithNewSearchFilter(QString);
    void ADD_TAG();
    void REMOVE_TAG();
    void CHANGE_NAME_TAG_OR_STOCK_DISABLED_TAGS(QListWidgetItem *item);

    void UI_EXPOR_TO_FILE(const int type);
    void FIRE_UP_TRASH_BIN_DIALOG();

private:
    void LoadExportToViewerPage(ExportType type, QList<Note*>& list, QWidget* viewerPage = 0, Viewer* viewer = 0);

    Ui::MainWindow *ui;
    QWidget *editorWidget;
    QVBoxLayout *layout;

    QMenu *menuFichier, *menuEdition;

    QTabWidget *tab;
    QWidget *EditorPage;
    QWidget *htmlViewerPage;
    QWidget *texViewerPage;
    QWidget *textViewerPage;

    NotesManager *nm;
    TagManager *tm;

    QSet<QString> openedFiles;

    HtmlViewer * hv;
    TexViewer * tv;
    TextViewer * textv;

    // On peut utilise qu'une seule ressource
    QList<Note*> ressources;
    QSet<Tag*> tags;
    QSet<Tag*> tagsDisabled;

    TreeModel* sideBarModel;


    int lastTabIndex;
};

#endif // MAINWINDOW_H
