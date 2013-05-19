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
#include "Editor.h"

class ArticleEditor : public Editor
{
    Q_OBJECT
public:
    explicit ArticleEditor(Note *, QWidget *parent = 0);

    QLineEdit *getTitle() const;
    void setTitle(QLineEdit *value);

    QTextEdit *getText() const;
    void setText(QTextEdit *value);

    Article *getRessource() const;
    void setRessource(Article *value);

    QTextEdit *getTextWidget() const;
    void setTextWidget(QTextEdit *value);

signals:

public slots:
    void BACKEND_SET_CONTENT();

private:
    QTextEdit *textWidget;

    Article *ressource;
    NotesManager *nm;
};

#endif // ARTICLEEDITOR_H
