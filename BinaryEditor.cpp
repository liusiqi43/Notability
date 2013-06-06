#include "BinaryEditor.h"
#include "Binary.h"
/***
 * BinaryEditor
 */

QLineEdit *BinaryEditor::getDescriptionWidget() const
{
    return descriptionWidget;
}

void BinaryEditor::setDescriptionWidget(QLineEdit *value)
{
    descriptionWidget = value;
}

BinaryEditor::BinaryEditor(Binary *b, QWidget *parent)
    :Editor(b, parent), ressource(b)
{
    descriptionWidget = new QLineEdit(ressource->getDescription());

    QObject::connect(descriptionWidget, SIGNAL(textChanged(QString)), this, SLOT(UI_ENABLE_SAVE_BUTTON_AND_UPDATE_SIDEBAR()));
    QObject::connect(this, SIGNAL(destroyed()), this, SLOT(CLOSING()));
}
