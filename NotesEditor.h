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

#include "Notes.h"
#include "ArticleEditor.h"

class NotesEditor : public QMainWindow
{
    Q_OBJECT
public:
    explicit NotesEditor(QWidget *parent = 0);
    
signals:
    
public slots:
    void UI_OPEN_FILE();
    void UI_INFORM_NOT_IMPLEMENTED();
    
private:
    QMenu *menuFichier, *menuEdition;
    QWidget *articleEditorPage;
    NotesManager *nm;
    QTabWidget *onglets;
};

#endif // NOTESEDITOR_H
