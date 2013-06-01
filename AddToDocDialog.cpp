#include "AddToDocDialog.h"
#include "NotesManager.h"
#include "Note.h"
#include "ui_AddToDocDialog.h"
#include <QListWidgetItem>

AddToDocDialog::AddToDocDialog(Note *n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddToDocDialog)
{
    ui->setupUi(this);
    nm = &NotesManager::getInstance();
    activatedDocuments = new QSet<Document*>();

    for(QSet<Document*>::const_iterator it=nm->beginDocumentContainer(); it!=nm->endDocumentContainer(); ++it){
        if((*it)==n)
            continue;
        QListWidgetItem* item = new QListWidgetItemWithpDocument((*it)->getTitle(), *it, ui->docListWidget);
        item->setData(0, (*it)->getTitle());
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        if(n->belongs(*it)){
            item->setCheckState(Qt::Checked);
            activatedDocuments->insert(*it);
        }
        else
            item->setCheckState(Qt::Unchecked);
    }
    QObject::connect(ui->docListWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(STOCK_ACTIVATED_DOC(QListWidgetItem*)));
}

void AddToDocDialog::STOCK_ACTIVATED_DOC(QListWidgetItem* item){
    if(item->checkState()==Qt::Checked){
        qDebug()<<"Getting "<< item->data(0) << "checked";
        activatedDocuments->insert(static_cast<QListWidgetItemWithpDocument*>(item)->getRessource());
    }
    else{
        qDebug()<<"Getting "<< item->data(0) << "unchecked";
        activatedDocuments->remove(static_cast<QListWidgetItemWithpDocument*>(item)->getRessource());
    }
}

AddToDocDialog::~AddToDocDialog()
{
    delete ui;
}

QSet<Document *> *AddToDocDialog::getDocuments()
{
    return activatedDocuments;
}

Document *QListWidgetItemWithpDocument::getRessource() const
{
    return ressource;
}

void QListWidgetItemWithpDocument::setRessource(Document *value)
{
    ressource = value;
}
