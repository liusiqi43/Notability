#ifndef NOTESEDITOR_H
#define NOTESEDITOR_H

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

class Editor;
class HtmlViewer;
class Note;
class NotesManager;

class mainUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainUI(QWidget *parent = 0);
    
signals:
    
public slots:
    void UI_OPEN_FILE();
    void UI_INFORM_NOT_IMPLEMENTED();
    void UI_NEW_NOTE_EDITOR(const int type);
    void UI_TAB_CHANGE_HANDLER(int);
    
private:
    QWidget *mainWidget;
    QVBoxLayout *layout;

    QMenu *menuFichier, *menuEdition;

    QTabWidget *tab;
    QWidget *EditorPage;
    QWidget *htmlViewerPage;
    QWidget *texViewerPage;

    NotesManager *nm;

    Editor * noteEditor;
    HtmlViewer * hv;

    Note * ressource;

    int lastTabIndex;
};

#endif // NOTESEDITOR_H
