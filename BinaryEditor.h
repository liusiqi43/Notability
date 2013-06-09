#ifndef BINARYEDITOR_H
#define BINARYEDITOR_H

#include "Editor.h"
#include <QLineEdit>

class Binary;

/*!
 * \brief The BinaryEditor class Cette class fournit une implementation partielle pour les Editor Multimedias.
 */
class BinaryEditor: public Editor
{
    Q_OBJECT
public:
    explicit BinaryEditor(Binary *b, QWidget *parent = 0);

    /*!
     * \brief getDescriptionWidget Traitement au niveau des descriptions
     * \return
     */
    QLineEdit *getDescriptionWidget() const;
    void setDescriptionWidget(QLineEdit *value);

signals:

public slots:
    /*!
     * \brief CLOSING Methode virtuelle pure qui impose que chaque sous classes doit implementer une methode CLOSING qui assure un comportement normalement apres fermeture du Editor (le video doit s'arreter apres le changement de onglet par exemple)
     */
    virtual void CLOSING() = 0;
private:
    QLineEdit *descriptionWidget;
    Binary *ressource;
};
#endif // BINARYEDITOR_H
