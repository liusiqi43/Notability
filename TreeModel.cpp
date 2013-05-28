#include "TreeModel.h"
#include "TreeItem.h"
#include "Note.h"
#include "NotesManager.h"
#include "Document.h"
#include <QList>


TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    nm = &NotesManager::getInstance();
    QVector<QVariant> rootData;

    rootData << "Root";

    rootItem = new TreeItem(rootData);
    setupModelData(rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value,
                        int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void TreeModel::deployDocument(Document* current, QList<TreeItem*>* parents, int& pos, QList<int>* indent){
    pos += 2;
    QVector<QVariant> data;
    data << current->getTitle();

    parents->append(new TreeItem(data, parents->last()));
    indent->append(pos);

    for (nListIt it = current->begin(); it!=current->end(); ++it){
        if((*it)->isDocument()){
           deployDocument(dynamic_cast<Document*>(*it), parents, pos, indent);
           parents->pop_back();
           indent->pop_back();
        }
        else if(!(*it)->isDocument()){
           // Not a document, on l'affiche comme une file
           QVector<QVariant> data;
           data << (*it)->getTitle();

           TreeItem *parent = parents->last();
           parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
           for (int column = 0; column < data.size(); ++column)
               parent->child(parent->childCount() - 1)->setData(column, data[column]);
        }
    }
}


void TreeModel::setupModelData(TreeItem* parent)
 {
     QList<TreeItem*> parents;
     QList<int> indentations;
     parents << parent;
     indentations << 0;

     for (nListIt it = nm->begin(); it!=nm->end(); ++it){
        int position = 0;
        if((*it)->isDocument()){
            deployDocument(dynamic_cast<Document*>(*it), &parents, position, &indentations);
            parents.pop_back();
            indentations.pop_back();
        }
        else {
            QVector<QVariant> data;
            data << (*it)->getTitle();

            // Append a new item to the current parent's list of children.
            TreeItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < data.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, data[column]);
        }
     }
 }