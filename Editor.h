#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

#include "Notes.h"

/**
 * @brief The Editor class: Editor::Editor, base class for Article editor, Binary Editor. Abstract class
 */
class Editor : public QWidget
{
    Q_OBJECT

    Note * ressource;

    QLineEdit * titleWidget;

    QPushButton * btnSave;

    void BACKEND_SAVE_TITLE();
    void UI_INFORM_USER_OF_SAVE();

    virtual void BACKEND_SET_CONTENT() = 0;

protected:
    QVBoxLayout *layout;

public:
    explicit Editor(Note *, QWidget *parent = 0);
    
    Note *getRessource() const;
    void setRessource(Note *value);

    QLineEdit *getTitleWidget() const;
    void setTitleWidget(QLineEdit *value);

    QPushButton *getBtnSave() const;
    void setBtnSave(QPushButton *value);

signals:
    
public slots:
    void UI_ENABLE_SAVE_BUTTON();
    void BACKEND_SAVE();
    
};

#endif // EDITOR_H
