#ifndef TRASHDIALOG_H
#define TRASHDIALOG_H

#include <QDialog>

class DeletedNote;
class QListWidgetItem;

namespace Ui {
class TrashDialog;
}

/*!
 * \brief The TrashDialog class La dialog qui permet de restaurer ou supprimer definitivement les notes.
 */
class TrashDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TrashDialog(QWidget *parent = 0);
    ~TrashDialog();
    
private:
    Ui::TrashDialog *ui;

public slots:
    void HANDLER_RESBTN_PRESSED();
    void HANDLER_DELBTN_PRESSED();
};

#endif // TRASHDIALOG_H
