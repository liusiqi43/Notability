#include "AddTagToNoteDialog.h"
#include "ui_AddTagToNoteDialogs.h"
#include "TagManager.h"



AddTagToNoteDialog::AddTagToNoteDialog(Note *n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTagToNoteDialog)
{
    ui->setupUi(this);
    tm = &TagManager::getInstance();
    activatedTags = new QSet<Tag*>();

    for(QSet<Tag *>::const_iterator it = tm->begin(); it!=tm->end(); ++it){
        QListWidgetItem* item = new QListWidgetItemWithpTag((*it)->getName(), *it, ui->listWidget);
        item->setData(0, (*it)->getName());
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        if(n->getTags().contains(*it)){
            item->setCheckState(Qt::Checked);
            activatedTags->insert(*it);
        }
        else
            item->setCheckState(Qt::Unchecked);
    }
    QObject::connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(STOCK_ACTIVATED_TAGS(QListWidgetItem*)));
}

void AddTagToNoteDialog::STOCK_ACTIVATED_TAGS(QListWidgetItem * item)
{
    if(item->checkState()==Qt::Checked){
        qDebug()<<"Getting "<< item->data(0) << "checked";
        activatedTags->insert(static_cast<QListWidgetItemWithpTag*>(item)->getRessource());
    }
    else{
        qDebug()<<"Getting "<< item->data(0) << "unchecked";
        activatedTags->remove(static_cast<QListWidgetItemWithpTag*>(item)->getRessource());
    }
}

AddTagToNoteDialog::~AddTagToNoteDialog()
{
    delete ui;
}

QSet<Tag *>* AddTagToNoteDialog::getTags()
{
    return activatedTags;
}
