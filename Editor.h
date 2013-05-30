#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Note;

/**
 * @brief The Editor class: Editor::Editor, base class for Article editor, Binary Editor. Abstract class
 */
class Editor : public QWidget
{
    Q_OBJECT
    QLineEdit * titleWidget;
    QWidget * contentWidget;
    QWidget * buttonsWidget;
    Note * ressource;
    QPushButton * btnSave;
    QPushButton * btnClose;
    QPushButton * btnMove;
    QPushButton * btnTag;
    QVBoxLayout * editorBaseLayout;

    void BACKEND_SET_TITLE();
    virtual void BACKEND_SET_CONTENT() = 0;
    void UI_INFORM_USER_OF_SAVE();

protected:
    QVBoxLayout *contentLayout;
    QHBoxLayout *buttonsLayout;

public:

    explicit Editor(Note *n, QWidget *parent = 0);

    QLineEdit *getTitleWidget() const;
    void setTitleWidget(QLineEdit *value);

    QPushButton *getBtnSave() const;
    void setBtnSave(QPushButton *value);

    Note *getRessource() const;
    void setRessource(Note *value);

    bool operator==(const Editor& rhs);

    QPushButton *getBtnClose() const;
    void setBtnClose(QPushButton *value);

    QPushButton *getBtnMove() const;
    void setBtnMove(QPushButton *value);

    QPushButton *getBtnTag() const;
    void setBtnTag(QPushButton *value);

signals:

public slots:
    void UI_ENABLE_SAVE_BUTTON();
    void BACKEND_SAVE();
    void BACKEND_SET();

};

#endif // EDITOR_H
