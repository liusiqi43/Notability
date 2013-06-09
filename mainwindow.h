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
#include <QUndoStack>
#include <QUndoView>
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

/*!
 * \brief The MainWindow class Widget Central qui comporte un sideBar qui affiche une hierarchie des Notes, une liste des tags, les menus, et les Editeurs et Viewers.
 */
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
    void createUndoView();

private:
    /*!
     * \brief LoadExportToViewerPage Methode qui unifie le chargement des Exportation dans les Viewer.
     * Pour un export HTML par exemple. Le note contenus dans \link<list> sera exporte en html et en suite charge dans un HTML viewer.
     * Si viewer = 0, on utilise cette methode pour generer les fichiers directement. Ceci permet de ne pas dupliquer le code pour exporter les notes.
     * \param type le type de Exportation
     * \param list list des notes a exporter.
     * \param viewerPage viewerPage ou on va afficher le resultat
     * \param viewer viewer qui prend en charge de l'affichage du contenu
     */
    void LoadExportToViewerPage(ExportType type, QList<Note*>& list, QWidget* viewerPage = 0, Viewer* viewer = 0);
    void createActions();
    void layingOutStuff();
    /*!
     * \brief preparingUndoableCommands Cette fonction preparer les UndoableCommands. Et une liste des undoable historique.
     */
    void preparingUndoableCommands();

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
    QSet<Tag*> tagsDisabled;

    /*!
     * \brief sideBarModel Selon le framework MVC du Qt, nous avons develope un model pour le TreeView qui permet d'affichier une hierarechie des Notes.
     */
    TreeModel* sideBarModel;

    QAction * undoAction, *redoAction;
    QAction *historyBtn;
    /*!
     * \brief undoStack Une pile des undoables commands. Cette stack va stocker toutes les actions effectue concernant la manipulation des tags. cf. \link<UndoableActions.h>
     */
    QUndoStack *undoStack;
    QUndoView *undoView;

    int lastTabIndex;
};

#endif // MAINWINDOW_H
