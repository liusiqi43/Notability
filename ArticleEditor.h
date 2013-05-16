#ifndef ARTICLEEDITOR_H
#define ARTICLEEDITOR_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QDebug>
#include "Notes.h"

class ArticleEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ArticleEditor(Article *, QWidget *parent = 0);

signals:

public slots:
    void UI_ENABLE_SAVE_BUTTON();
    void BACKEND_ARTICLE_SAVE();
    void CLOSE_AND_RELEASE_MANAGER();
private:
    void BACKEND_ARTICLE_SAVE_TITLE();
    void BACKEND_ARTICLE_SAVE_TEXT();
    void UI_INFORM_USER_OF_SAVE();
    QVBoxLayout *layout;

    QPushButton * btnQuit;
    QPushButton * btnSave;
    QLineEdit *title;
    QTextEdit *text;

    Article *ressource;
    NotesManager *nm;
};

#endif // ARTICLEEDITOR_H
