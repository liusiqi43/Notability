#ifndef EDITORS_H
#define EDITORS_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include "BaseEditor.h"

class Article;
class Binary;
class ImageNote;

class ArticleEditor : public Editor
{
    Q_OBJECT
public:
    explicit ArticleEditor(Article *, QWidget *parent = 0);

    QTextEdit *getTextWidget() const;
    void setTextWidget(QTextEdit *value);

    Article *getRessource() const;
    void setRessource(Article *value);

    QString toHtml() const;
signals:

public slots:
    void BACKEND_SET_CONTENT();

private:
    QTextEdit *textWidget;
    Article *ressource;
};

class BinaryEditor: public Editor
{
    Q_OBJECT
public:
    explicit BinaryEditor(Binary *b, QWidget *parent = 0);

    QLineEdit *getDescriptionWidget() const;
    void setDescriptionWidget(QLineEdit *value);

    Binary *getRessource() const;
    void setRessource(Binary *value);

signals:

public slots:
private:
    QLineEdit *descriptionWidget;
    Binary *ressource;
};


class ImageNoteEditor : public BinaryEditor
{
    Q_OBJECT
public:
    explicit ImageNoteEditor(ImageNote *img, QWidget *parent = 0);

    ImageNote *getRessource() const;
    void setRessource(ImageNote *value);

    QString toHtml() const;

signals:

public slots:
    void BACKEND_SET_CONTENT();
    void LOAD_IMAGE();

private:
    QPushButton *btnAddImage;
    QPixmap image;
    QLabel *imageWidget;
    ImageNote *ressource;
    QString currentImgPath;
};



#endif // EDITORS_H
