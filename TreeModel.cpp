//#include "TreeModel.h"
//#include "TreeItem.h"
//#include "Note.h"
//#include "NotesManager.h"
//#include "Document.h"
//#include <QList>

//TreeModel::TreeModel(QObject *parent)
//    : QAbstractItemModel(parent)
//{
//    nm = &NotesManager::getInstance();
//    QList<Note*> rootData;
//    Document* defaultDoc = &nm->getNewNote(document);
//    defaultDoc->setTitle("Notebooks");
//    rootData << defaultDoc;
//    rootItem = new TreeItem(rootData);
//    setupModelData(rootItem);
//}

//TreeModel::~TreeModel()
// {
//     delete rootItem;
// }

//QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
//             const
// {
//     if (!hasIndex(row, column, parent))
//         return QModelIndex();

//     TreeItem *parentItem;

//     if (!parent.isValid())
//         parentItem = rootItem;
//     else
//         parentItem = static_cast<TreeItem*>(parent.internalPointer());

//     TreeItem *childItem = parentItem->child(row);
//     if (childItem)
//         return createIndex(row, column, childItem);
//     else
//         return QModelIndex();
// }

//QModelIndex TreeModel::parent(const QModelIndex &index) const
// {
//     if (!index.isValid())
//         return QModelIndex();

//     TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
//     TreeItem *parentItem = childItem->parent();

//     if (parentItem == rootItem)
//         return QModelIndex();

//     return createIndex(parentItem->row(), 0, parentItem);
// }

//int TreeModel::rowCount(const QModelIndex &parent) const
// {
//     TreeItem *parentItem;
//     if (parent.column() > 0)
//         return 0;

//     if (!parent.isValid())
//         parentItem = rootItem;
//     else
//         parentItem = static_cast<TreeItem*>(parent.internalPointer());

//     return parentItem->childCount();
// }

//int TreeModel::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
//    else
//        return rootItem->columnCount();
//}

//QVariant TreeModel::data(const QModelIndex &index, int role) const
// {
//     if (!index.isValid())
//         return nm->getNewNote(document).getTitle();

//     if (role != Qt::DisplayRole)
//         return nm->getNewNote(document).getTitle();

//     TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

//     return item->data(index.column());
// }


//Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
// {
//     if (!index.isValid())
//         return 0;

//     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
// }


//QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
//                                int role) const
// {
//     if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//         return rootItem->data(section);

//     return nm->getNewNote(document).getTitle();
// }

//void deployDocument(Document* current, QList<TreeItem*>* parents, int& pos, QList<int>* indent){
//    pos += 2;
//    parents->append(*current);
//    indent->append(pos);

//    for (QSet<Note*>::const_iterator it = current->begin(); it!=current->end(); ++it){
//        if((*it)->isDocument() && !(*it)->isDisplayed()){
//           deployDocument(dynamic_cast<Document*>(*it), parents, pos, indent);
//           parents->pop_back();
//           indent->pop_back();
//        }
//        else if(!(*it)->isDocument()){
//           // Not a document, on l'affiche comme une file
//           parents->last()->appendChild(new TreeItem((*it), parents->last()));
//        }
//        (*it)->setDisplayed(true);
//    }
//}


//void TreeModel::setupModelData(TreeItem *parent)
// {
//    if(!nm)
//        nm = &NotesManager::getInstance();

//     QList<TreeItem*> parents;
//     QList<int> indentations;
//     parents << parent;
//     indentations << 0;

//     for (QSet<Note*>::const_iterator it = nm->begin(); it!=nm->end(); ++it){
//        int position = 0;
//        if((*it)->isDocument() && !(*it)->isDisplayed()){
//            deployDocument(dynamic_cast<Document*>(*it), &parents, position, &indentations);
//        }
//     }
////     while (number < lines.count()) {
////         int position = 0;
////         while (position < lines[number].length()) {
////             if (lines[number].mid(position, 1) != " ")
////                 break;
////             position++;
////         }

////         QString lineData = lines[number].mid(position).trimmed();

////         if (!lineData.isEmpty()) {
////             // Read the column data from the rest of the line.
////             QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
////             QList<QVariant> columnData;
////             for (int column = 0; column < columnStrings.count(); ++column)
////                 columnData << columnStrings[column];

////             if (position > indentations.last()) {
////                 // The last child of the current parent is now the new parent
////                 // unless the current parent has no children.

////                 if (parents.last()->childCount() > 0) {
////                     parents << parents.last()->child(parents.last()->childCount()-1);
////                     indentations << position;
////                 }
////             } else {
////                 while (position < indentations.last() && parents.count() > 0) {
////                     parents.pop_back();
////                     indentations.pop_back();
////                 }
////             }

////             // Append a new item to the current parent's list of children.
////             parents.last()->appendChild(new TreeItem(columnData, parents.last()));
////         }

////         number++;
////     }
// }
