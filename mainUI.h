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

#include "Notes.h"
#include "BaseEditor.h"
#include "htmlViewer.h"
#include "NotesManager.h"

class mainUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainUI(QWidget *parent = 0);
    
signals:
    
public slots:
    void UI_OPEN_FILE();
    void UI_OPEN_IMAGENOTE();
    void UI_INFORM_NOT_IMPLEMENTED();
    void UI_TAB_CHANGE_HANDLER(int);
    
private:
    QWidget *mainWidget;
    QVBoxLayout *layout;

    QMenu *menuFichier, *menuEdition;

    QTabWidget *tab;
    QWidget *EditorPage;
    QWidget *htmlViewerPage;

    NotesManager *nm;

    Editor * noteEditor;
    HtmlViewer * hv;

    Note * ressource;

    int lastTabIndex;
};

#endif // NOTESEDITOR_H
