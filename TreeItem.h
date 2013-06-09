#ifndef TREEITEM_H
#define TREEITEM_H
#include <QVariant>
#include <QVector>
#include <QString>

class Note;

/*!
 * \brief The TreeItem class Cette classe est une implementation du model MVC propose par Qt MVC framework.
 * Il s'agit d'un implementation personalisee de TreeItem. Cette classes sert a faciliter la gestion du TreeView.
 * Chaque TreeItem comporte zero ou plusieurs childrens, qui sont a leurs tour potentiellement le parent des children.
 * Ceci permet donc de former un arbre.
 * \todo {Utilisation d'un iterator profondeur d'abord va largement facilter le code, on pourrait s'en servir pour la reecriture du programme.}
 */
class TreeItem
 {
 public:
     TreeItem(const QVector<QVariant> &data, TreeItem *parent = 0);
     ~TreeItem();

     TreeItem *child(int number);
     int childCount() const;
     int columnCount() const;
     /*!
      * \brief data Ici on utilise qu'un seul colomn, qui est le titre du note.
      * \param column egale a 0 dans ce cas la.
      * \return
      */
     QVariant data(int column) const;
     bool insertChildren(int position, int count, int columns);
     bool insertColumns(int position, int columns);
     TreeItem *parent();
     bool removeChildren(int position, int count);
     bool removeColumns(int position, int columns);
     int childNumber() const;
     bool setData(int column, const QVariant &value, Note * underlyingNote);
     /*!
      * \brief updateUnderlyingNoteTitle A chaque TreeItem on lui associe une Note. Ceci permet de mettre a jour le titre du note a partir du TreeView
      * \deprecated{cette methode n'est plus utilise car l'interface pour editer le titre est egalement double-click. Ceci va creer des confusion pour l'utilisateurs}
      */
     void updateUnderlyingNoteTitle(const QVariant&);

     Note *getItemId() const;
     /*!
      * \brief setItemId chaque Item est characterise par son Note associe. Pour la raison historique, on l'appelle ID
      * \param value
      */
     void setItemId(Note *value);

private:
     /*!
      * \brief childItems Chaque TreeItem comporte zero ou plusieurs childrens, qui sont a leurs tour potentiellement le parent des children.
      */
     QList<TreeItem*> childItems;
     QVector<QVariant> itemData;
     Note * itemId;
     /*!
      * \brief IDlock \deprecated{utilise pour editer le titre du document depuis TreeView.}
      * \deprecated{cette methode n'est plus utilise car l'interface pour editer le titre est egalement double-click. Ceci va creer des confusion pour l'utilisateurs}
      */
     bool IDlock;
     TreeItem *parentItem;
 };

#endif // TREEITEM_H
