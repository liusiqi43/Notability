#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QListWidget>

class NotesManager;
class FilterKit;
class Note;
class TreeItem;
class Document;
class TagManager;

/*!
 * \brief The TreeModel class Cette classe conforme a la framework MVC du Qt. Ceci permet d'afficher une TreeView qui montre clairement la relations entre les documents et les notes.
 */
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    /*!
     * \brief headerData Methode virtuelle du \link<QAbstractListModel>. Ceci permet de redefinir le comportement de headerData (c'est le data qui sera affiche sur chaque item.)
     * \param section
     * \param orientation
     * \param role
     * \return
     */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    /*!
     * \brief flags ces flags permettent de definir le comportement du item lors qu'on double click dessus.
     * \param index l'indice de TreeItem
     * \return
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;
    /*!
     * \brief setData Cette methode permet de declencher un signal setData, qui permet de mettre a jour le titre des documents
     * \deprecated {pour la meme raison mentionne dans \link<TreeItem.h>}
     * \param index
     * \param value
     * \param role
     * \return
     */
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole);

    /*!
     * \brief insertColumns Methode neccesaire lors qu'on sous classer QAbstractItemModel
     * \param position
     * \param columns
     * \param parent
     * \return
     */
    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    /*!
     * \brief insertColumns Methode neccesaire lors qu'on sous classer QAbstractItemModel
     * \param position
     * \param columns
     * \param parent
     * \return
     */
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    /*!
     * \brief insertColumns Methode neccesaire lors qu'on sous classer QAbstractItemModel
     * \param position
     * \param columns
     * \param parent
     * \return
     */
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    /*!
     * \brief insertColumns Methode neccesaire lors qu'on sous classer QAbstractItemModel
     * \param position
     * \param columns
     * \param parent
     * \return
     */
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    /*!
     * \brief getItem
     * \param index
     * \return Retourne l'item associe a un indice index.
     */
    TreeItem *getItem(const QModelIndex &index) const;

private:
    /*!
     * \brief deployDocument Cette methode deployer un document recursivement dans un treeview.
     * L'ensemble des Filtres actives seront applique dans la metode setupModelData();
     * Lors qu'on ajoute un nouveau filtre, il suffit de l'ajouter dans le singleton FilterKit pour qu'il entre en effet.
     * \todo {replacer cette methode en utilisant l'iterateur profondeur d'abord}
     * \param current
     * \param parents une QList qui enreigistre l'item qui est le parent pendant ce deploiement courant
     * \param indent une QList des indents qui stock indentation correcte pour item actuelle
     */
    void deployDocument(Document* current, QList<TreeItem*>& parents, QList<int>& indent);
    /*!
     * \brief setupModelData cet methode initialise les donnes dans le TreeView. Elle fait appel a deployDocument recursivement.
     * \param parent
     */
    void setupModelData(TreeItem *parent);

    /*!
     * \brief rootItem TreeItem racine
     */
    TreeItem *rootItem;

    NotesManager *nm;

    /*!
     * \brief filterKit L'ensemble des Filtres actives seront applique dans la metode setupModelData();
     */
    FilterKit *filterKit;

    TagManager *tm;

    QListWidget* tagListModel;


};
#endif // TREEMODEL_H
