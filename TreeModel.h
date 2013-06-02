#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QListWidget>

class NotesManager;
class Note;
class TreeItem;
class Document;
class TagManager;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole);

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    TreeItem *getItem(const QModelIndex &index) const;

private:
    void deployDocument(Document* current, QList<TreeItem*>& parents, QList<int>& indent);
    void setupModelData(TreeItem *parent);

    TreeItem *rootItem;

    NotesManager *nm;

    TagManager *tm;

    QListWidget* tagListModel;


};
#endif // TREEMODEL_H
