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
public:
    static MainWindow* getInstance();
    static void freeInstance();
    
signals:

public slots:
    void UI_OPEN_FILE();
    void UI_INFORM_NOT_IMPLEMENTED();
    void UI_NEW_NOTE_EDITOR(const int type);
    void UI_TAB_CHANGE_HANDLER(int);
    void BACKEND_CLOSING();
    void UI_LOAD_FROM_SIDE_BAR(const QModelIndex &index);
    void updateSideBar();
    void updateTagList();
private:
    void LoadExportToViewerPage(ExportType type, QList<Note*>& list, QWidget* viewerPage, Viewer* viewer);

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

    QList<Note*> ressources;
    QSet<Tag*> tags;

    TreeModel* sideBarModel;
    QListWidget* tagL;

    int lastTabIndex;
};

#endif // MAINWINDOW_H
