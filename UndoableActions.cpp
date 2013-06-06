#include "UndoableActions.h"
#include "TagManager.h"
#include "mainwindow.h"
#include <QListWidget>
#include <QUndoCommand>
#include <QDebug>
#include <QDateTime>

AddNewTagCmd::AddNewTagCmd(QListWidget *l, QUndoCommand* parent)
    :QUndoCommand(parent), list(l), tag(0), item(0)
{
    setText("Add New Tag");
}

void AddNewTagCmd::redo(){
    if(!tag){
        tag = TagManager::getInstance().getTag("New Tag");
    }

    TagManager::getInstance().addTag(tag);
    bool oldState = list->blockSignals(true);
    item = new ListWidgetItemCheckTag("New Tag", tag, list);
    list->blockSignals(oldState);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable); // set checkable flag
    item->setCheckState(Qt::Checked);
//    qDebug() << "tag addr: " << tag << " Name: " << tag->getName();
}

void AddNewTagCmd::undo(){

    ListWidgetItemCheckTag *item = 0;
    for(int i=0; i<list->count(); i++){
        item = dynamic_cast<ListWidgetItemCheckTag*>(list->item(i));
        if(item->getTag() == tag){
            break;
        }
    }

    if(item){
        TagManager::getInstance().removeTag(tag);
        bool oldState = list->blockSignals(true);
        delete item;
        list->blockSignals(oldState);
        item = 0;
    }
}

RemoveCurrentTagCmd::RemoveCurrentTagCmd(QListWidget *l, ListWidgetItemCheckTag* t, QUndoCommand *parent)
    :QUndoCommand(parent), tag(t->getTag()),  list(l)
{
    setText("Remove "+tag->getName());
}

void RemoveCurrentTagCmd::redo(){
    TagManager *tagM = &TagManager::getInstance();
    ListWidgetItemCheckTag *item = 0;
    for(int i=0; i<list->count(); i++){
        item = dynamic_cast<ListWidgetItemCheckTag*>(list->item(i));
        if(item->getTag() == tag){
            break;
        }
    }
    if(item){
        checkstate = item->checkState();
        assos = tag->getAssocs();
        tagM->removeTag(tag);
        bool oldState = list->blockSignals(true);
        delete item;
        list->blockSignals(oldState);
    }
}

void RemoveCurrentTagCmd::undo(){
    bool oldState = list->blockSignals(true);
    TagManager *tagM = &TagManager::getInstance();
    for(QSet<Note*>::iterator it = assos.begin(); it != assos.end(); ++it){
        if(*it)
            tagM->addTagToNote(tag, *it);
    }
    tagM->addTag(tag);
    ListWidgetItemCheckTag *item = new ListWidgetItemCheckTag(tag->getName(), tag, list);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable); // set checkable flag
    item->setCheckState(checkstate);
    list->blockSignals(oldState);
}

bool EditCurrentTagCmd::first = true;

EditCurrentTagCmd::EditCurrentTagCmd(ListWidgetItemCheckTag* i, QListWidget *l, QUndoCommand *parent)
    :QUndoCommand(parent)
{
    tag = i->getTag();
    oldName = tag->getName();
    newName = i->data(0).toString();
    list = l;
    setText(oldName+"=>"+newName);
}


void EditCurrentTagCmd::redo()
{
    if(list->findItems(newName, Qt::MatchExactly).count()<=1){
        ListWidgetItemCheckTag *item = 0;
        for(int i=0; i<list->count(); i++){
            item = dynamic_cast<ListWidgetItemCheckTag*>(list->item(i));
            if(item->getTag() == tag){
                break;
            }
        }
        if(item){
            bool oldState = list->blockSignals(true);
            item->setData(0, newName);
            list->blockSignals(oldState);
            tag->setName(newName);
        }
    }
    else{
        QMessageBox::warning(MainWindow::getInstance(), "Duplicate tag", "There is already a tag named "+newName);
        return;
        ListWidgetItemCheckTag *item = 0;
        for(int i=0; i<list->count(); i++){
            item = dynamic_cast<ListWidgetItemCheckTag*>(list->item(i));
            if(item->getTag() == tag){
                break;
            }
        }
        if(item){
            bool oldState = list->blockSignals(true);
            item->setData(0, oldName);
            list->blockSignals(oldState);
            tag->setName(oldName);
        }
    }
}

void EditCurrentTagCmd::undo()
{
    if(list->findItems(oldName, Qt::MatchExactly).count()<=1){
        ListWidgetItemCheckTag *item = 0;
        for(int i=0; i<list->count(); i++){
            item = dynamic_cast<ListWidgetItemCheckTag*>(list->item(i));
            if(item->getTag() == tag){
                break;
            }
        }
        if(item){
            bool oldState = list->blockSignals(true);
            item->setData(0, oldName);
            list->blockSignals(oldState);
            tag->setName(oldName);
        }
    }
    else{
        QMessageBox::warning(MainWindow::getInstance(), "Duplicate tag", "There is already a tag named "+oldName);
        ListWidgetItemCheckTag *item = 0;
        for(int i=0; i<list->count(); i++){
            item = dynamic_cast<ListWidgetItemCheckTag*>(list->item(i));
            if(item->getTag() == tag){
                break;
            }
        }
        if(item){
            bool oldState = list->blockSignals(true);
            item->setData(0, newName);
            list->blockSignals(oldState);
            tag->setName(newName);
        }
    }
}

