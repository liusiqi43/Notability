#ifndef TREEITEM_H
#define TREEITEM_H
#include <QVariant>
#include <QVector>
#include <QString>

class Note;

class TreeItem
 {
 public:
     TreeItem(const QVector<QVariant> &data, TreeItem *parent = 0);
     ~TreeItem();

     TreeItem *child(int number);
     int childCount() const;
     int columnCount() const;
     QVariant data(int column) const;
     bool insertChildren(int position, int count, int columns);
     bool insertColumns(int position, int columns);
     TreeItem *parent();
     bool removeChildren(int position, int count);
     bool removeColumns(int position, int columns);
     int childNumber() const;
     bool setData(int column, const QVariant &value, Note * underlyingNote);
     void updateUnderlyingNoteTitle(const QVariant&);

     Note *getItemId() const;
     void setItemId(Note *value);

private:
     QList<TreeItem*> childItems;
     QVector<QVariant> itemData;
     Note * itemId;
     bool IDlock;
     TreeItem *parentItem;
 };

#endif // TREEITEM_H
