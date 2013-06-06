#ifndef BINARYEDITOR_H
#define BINARYEDITOR_H

#include "Editor.h"
#include <QLineEdit>

class Binary;

class BinaryEditor: public Editor
{
    Q_OBJECT
public:
    explicit BinaryEditor(Binary *b, QWidget *parent = 0);

    QLineEdit *getDescriptionWidget() const;
    void setDescriptionWidget(QLineEdit *value);

signals:

public slots:
    virtual void CLOSING() = 0;
private:
    QLineEdit *descriptionWidget;
    Binary *ressource;
};
#endif // BINARYEDITOR_H
