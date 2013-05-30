#ifndef BINARYEDITOR_H
#define BINARYEDITOR_H

#include "Editor.h"
#include <QLineEdit>

class Binary;

class BinaryEditor: public Editor
{
    Q_OBJECT
public:
    explicit BinaryEditor(Binary *b, MainWindow *mw, QWidget *parent = 0);

    QLineEdit *getDescriptionWidget() const;
    void setDescriptionWidget(QLineEdit *value);

//    Binary *getRessource() const;
//    void setRessource(Binary *value);

signals:

public slots:
private:
    QLineEdit *descriptionWidget;
    Binary *ressource;
};
#endif // BINARYEDITOR_H
