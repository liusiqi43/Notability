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
#include <QStandardItem>
#include <QComboBox>

class Note;
class MainWindow;
class TreeItem;
class AddToDocDialog;

/**
 * @brief The Editor class: Editor::Editor, base class for Article editor, Binary Editor. Abstract class
 */
class Editor : public QWidget
{
    Q_OBJECT
    QWidget * titleWidget;
    QLineEdit * titleEditWidget;
    QWidget * contentWidget;
    QWidget * buttonsWidget;
    Note * ressource;
    QPushButton * btnSave;
    QPushButton * btnClose;
    QPushButton * btnDelete;
    QPushButton * btnTag;
    QPushButton * documentBtn;

    QVBoxLayout * editorBaseLayout;

    AddToDocDialog *dialog;

    MainWindow * mainWindow;
    QHBoxLayout* titleLayout;

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

    QPushButton *getBtnTag() const;
    void setBtnTag(QPushButton *value);

    void setTitleWidgetText(const QString& title);
    void setDocumentBtnText(const QString& doc);
signals:

public slots:
    void UI_ENABLE_SAVE_BUTTON_AND_UPDATE_SIDEBAR();
    void BACKEND_SAVE();
    void BACKEND_SET();

    void ADD_TAG_TO_NOTE();

    void updateDocBtnWithRessource(TreeItem *item);
    void FIRE_UP_DOC_DIALOG();
    void retrieveDataFromDocDialog();

    void REMOVE_NOTE_TO_TRASH();


};

#endif // EDITOR_H
