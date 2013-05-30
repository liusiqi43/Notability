#ifndef ARTICLEEDITOR_H
#define ARTICLEEDITOR_H

#include "Editor.h"
#include <QPlainTextEdit>

class Article;
class ArticleEditor : public Editor
{
    Q_OBJECT
public:
    explicit ArticleEditor(Article *, QWidget *parent = 0);

    QPlainTextEdit *getTextWidget() const;
    void setTextWidget(QPlainTextEdit *value);

signals:

public slots:
    void BACKEND_SET_CONTENT();

private:
    QPlainTextEdit *textWidget;
    Article *ressource;
};

#endif // ARTICLEEDITOR_H
