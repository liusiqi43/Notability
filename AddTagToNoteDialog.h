#ifndef ADDTAGTONOTEDIALOG_H
#define ADDTAGTONOTEDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "NotesManager.h"
#include "TagManager.h"

class Tag;

namespace Ui {
class AddTagToNoteDialog;
}

/*!
 * \brief The QListWidgetItemWithpTag class Cette classe hérite de la classe \link <QListWidgetItem> qui fournit un accesseur au \link <Tag> associé.
 */
class QListWidgetItemWithpTag : public QListWidgetItem{
    Tag *ressource;
public:
    QListWidgetItemWithpTag(const QString & text, Tag* tag, QListWidget * parent = 0, int type = Type)
        :QListWidgetItem(text, parent, type), ressource(tag){}

    Tag *getRessource() const {return ressource;}
    void setRessource(Tag *value) {ressource = value;}
};

/*!
 * \brief The AddTagToNoteDialog class Cette classe permet de récupérer les tags activés après sa fermeture.
 */
class AddTagToNoteDialog : public QDialog
{
    Q_OBJECT
    QSet<Tag *> *activatedTags;
    TagManager *tm;
public:
    explicit AddTagToNoteDialog(Note *n, QWidget *parent = 0);
    ~AddTagToNoteDialog();
    QSet<Tag *> *getTags();
    
private:
    Ui::AddTagToNoteDialog *ui;

public slots:
    void STOCK_ACTIVATED_TAGS(QListWidgetItem *item);
};

#endif // ADDTAGTONOTEDIALOG_H
