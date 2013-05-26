#ifndef ARTICLEEDITOR_H
#define ARTICLEEDITOR_H

#include "Editor.h"
//#include "Article.h"
class Article;
class ArticleEditor : public Editor
{
    Q_OBJECT
public:
    explicit ArticleEditor(Article *, QWidget *parent = 0);

    QTextEdit *getTextWidget() const;
    void setTextWidget(QTextEdit *value);

//    Article *getRessource() const;
//    void setRessource(Article *value);

signals:

public slots:
    void BACKEND_SET_CONTENT();

private:
    QTextEdit *textWidget;
    Article *ressource;
};

#endif // ARTICLEEDITOR_H
