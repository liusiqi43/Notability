//#include "TreeItem.h"
//#include "Note.h"
//#include <QList>

//TreeItem::TreeItem(const Note *data, TreeItem *parent)
//{
//    parentItem = parent;
//    itemData = data;
//}

//TreeItem::~TreeItem()
//{
//    qDeleteAll(childItems);
//}

//TreeItem *TreeItem::child(int row)
// {
//     return childItems.value(row);
// }

//int TreeItem::childCount() const
// {
//     return childItems.count();
// }
//int TreeItem::row() const
// {
//     if (parentItem)
//         return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

//     return 0;
// }

//int TreeItem::columnCount() const
// {
//     return itemData.count();
// }

//QString TreeItem::data(int column) const
// {
//     return itemData->getTitle();
// }


//TreeItem *TreeItem::parent()
// {
//     return parentItem;
// }

