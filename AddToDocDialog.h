#ifndef ADDTODOCDIALOG_H
#define ADDTODOCDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

class Note;
class NotesManager;
class Document;

namespace Ui {
class AddToDocDialog;
}

/*!
 * \brief The QListWidgetItemWithpDocument class Cette classe hérite de la classe \link<QListWidgetItem> qui fournit un accesseur au \link<Document> associé.
 */
class QListWidgetItemWithpDocument : public QListWidgetItem{
    Document* ressource;
public:
    QListWidgetItemWithpDocument(const QString & text, Document* doc, QListWidget * parent = 0, int type = Type)
        :QListWidgetItem(text, parent, type), ressource(doc){}

    Document *getRessource() const;
    void setRessource(Document *value);
};

/*!
 * \brief The AddToDocDialog class Cette classe permet de récupérer les documents activés après sa fermeture.
 */
class AddToDocDialog : public QDialog
{
    Q_OBJECT
    QSet<Document *> *activatedDocuments;
    NotesManager *nm;
public:
    explicit AddToDocDialog(Note* n, QWidget *parent = 0);
    ~AddToDocDialog();
    QSet<Document *> * getDocuments();
    
private:
    Ui::AddToDocDialog *ui;
public slots:
    void STOCK_ACTIVATED_DOC(QListWidgetItem *);
};

#endif // ADDTODOCDIALOG_H
