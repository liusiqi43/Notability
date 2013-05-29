#include "TreeItem.h"
#include "Note.h"
#include "NotesManager.h"
#include <QList>

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
    :IDlock(false)
{
    parentItem = parent;
    itemData = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

TreeItem *TreeItem::child(int row)
 {
     return childItems.value(row);
 }

int TreeItem::childCount() const
 {
    return childItems.count();
 }

int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const
 {
     return itemData.count();
 }

QVariant TreeItem::data(int column) const
 {
     return itemData.value(column);
 }

bool TreeItem::setData(int column, const QVariant &n, Note* ID)
 {
     if (column < 0 || column >= itemData.size())
         return false;
     itemData[column] = n;
     if(!IDlock && ID){
         itemId = ID;
         IDlock = true;
     }
     return true;
}

void TreeItem::updateUnderlyingNoteTitle(const QVariant & newTitle)
{
    this->itemId->setTitle(newTitle.toString());
}

bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

bool TreeItem::removeColumns(int position, int columns)
 {
     if (position < 0 || position + columns > itemData.size())
         return false;

     for (int column = 0; column < columns; ++column)
         itemData.remove(position);

     foreach (TreeItem *child, childItems)
         child->removeColumns(position, columns);

     return true;
 }

bool TreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, NotesManager::getInstance().getNewNote(document).getTitle());

    foreach (TreeItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}

TreeItem *TreeItem::parent()
 {
     return parentItem;
 }


Note *TreeItem::getItemId() const
{
    return itemId;
}

void TreeItem::setItemId(Note *value)
{
    itemId = value;
}

