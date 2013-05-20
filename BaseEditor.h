#ifndef BASEEDITOR_H
#define BASEEDITOR_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

class Note;

/**
 * @brief The Editor class: Editor::Editor, base class for Article editor, Binary Editor. Abstract class
 */
class Editor : public QWidget
{
    Q_OBJECT
    QLineEdit * titleWidget;
    Note * ressource;
    QPushButton * btnSave;

    void BACKEND_SAVE_TITLE();
    void UI_INFORM_USER_OF_SAVE();

    virtual void BACKEND_SET_CONTENT() = 0;

public:
    QVBoxLayout *layout;

    explicit Editor(Note *n, QWidget *parent = 0);

    QLineEdit *getTitleWidget() const;
    void setTitleWidget(QLineEdit *value);

    QPushButton *getBtnSave() const;
    void setBtnSave(QPushButton *value);

    virtual QString toHtml() const = 0;

signals:
    
public slots:
    void UI_ENABLE_SAVE_BUTTON();
    void BACKEND_SAVE();
    
};

#endif // BASEEDITOR_H
