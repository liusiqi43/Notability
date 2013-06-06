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
        TagManager::getInstance().addTag(tag);
    }
    if(!item){
        item = new ListWidgetItemCheckTag("New Tag", tag, list);
    }
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable); // set checkable flag
    item->setCheckState(Qt::Checked);
    qDebug() << "tag addr: " << tag << " Name: " << tag->getName();
}

void AddNewTagCmd::undo(){
    if(item){
        TagManager::getInstance().removeTag(item->getTag());
        delete item;
        item = 0;
    }
}

RemoveCurrentTagCmd::RemoveCurrentTagCmd(QListWidget *l, ListWidgetItemCheckTag* t, QUndoCommand *parent)
    :QUndoCommand(parent), item(t), tag(t->getTag()),  list(l)
{
    setText("Remove "+tag->getName());
}

void RemoveCurrentTagCmd::redo(){
    TagManager *tagM = &TagManager::getInstance();
    checkstate = item->checkState();
    assos = tag->getAssocs();
    tagM->removeTag(item->getTag());
    delete item;
}

void RemoveCurrentTagCmd::undo(){
    TagManager *tagM = &TagManager::getInstance();
    for(QSet<Note*>::iterator it = assos.begin(); it != assos.end(); ++it){
        if(*it)
            tagM->addTagToNote(tag, *it);
    }
    tagM->addTag(tag);
    ListWidgetItemCheckTag *item = new ListWidgetItemCheckTag(tag->getName(), tag, list);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable); // set checkable flag
    item->setCheckState(checkstate);
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
        ListWidgetItemCheckTag *item;
        if(!list->findItems(newName, Qt::MatchExactly).isEmpty())
            item = dynamic_cast<ListWidgetItemCheckTag*>(list->findItems(newName, Qt::MatchExactly).first());
        else if (!list->findItems(oldName, Qt::MatchExactly).isEmpty())
            item = dynamic_cast<ListWidgetItemCheckTag*>(list->findItems(oldName, Qt::MatchExactly).first());
        if(item->getTag() == tag){
            tag->setName(newName);
            item->setData(0, newName);
        }
        EditCurrentTagCmd::first = false;
    }
    else{
        QMessageBox::warning(MainWindow::getInstance(), "Duplicate tag", "There is already a tag named "+newName);
        ListWidgetItemCheckTag *item = dynamic_cast<ListWidgetItemCheckTag*>(list->findItems(tag->getName(), Qt::MatchExactly).first());
        if(item->getTag() == tag)
            item->setData(0, oldName);
    }
}

void EditCurrentTagCmd::undo()
{
    if(list->findItems(oldName, Qt::MatchExactly).count()<=1){
        ListWidgetItemCheckTag *item = dynamic_cast<ListWidgetItemCheckTag*>(list->findItems(tag->getName(), Qt::MatchExactly).first());
        if(item->getTag() == tag){
            item->setData(0, oldName);
            tag->setName(oldName);
        }
    }
    else{
        QMessageBox::warning(MainWindow::getInstance(), "Duplicate tag", "Try to undo for your edited tag but there is already a tag named "+oldName);
    }
}

