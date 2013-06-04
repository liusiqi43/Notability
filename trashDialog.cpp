#include "trashDialog.h"
#include "ui_trashDialog.h"
#include "QListWidgetItemWithItemAndNote.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QWidget>
#include <QObject>
#include "Trash.h"

TrashDialog::TrashDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrashDialog)
{
    Trash *trash = Trash::getInstance();

    ui->setupUi(this);


    for (noteSetIt it = trash->begin(); it!=trash->end(); ++it) {

        QIcon icon = QIcon(":/images/play");
        QListWidgetItemWithNote *item = new QListWidgetItemWithNote((*it));
        item->setIcon(icon);
        ui->listWidget->addItem(item);
        QPushButton *buttonRes = new QPushButton(QIcon(":/images/restore"), "");
        QPushButton *buttonDel = new QPushButton(QIcon(":/images/delete"), "");
        buttonRes->setMaximumWidth(40);
        buttonDel->setMaximumWidth(40);
        QString title = (*it)->getNote()->getTitle();

        if(title.size() > 35){
            title.truncate(32);
            title+="...";
        }

        QLabel *label = new QLabel(title);
        QHBoxLayout *layout= new QHBoxLayout();
        layout->addWidget(label);
        layout->addWidget(buttonRes);
        layout->addWidget(buttonDel);
        QWidget *widget = new QWidget();
        widget->setLayout(layout);
        item->setSizeHint(widget->sizeHint());
        ui->listWidget->setItemWidget(item, widget);

        QObject::connect(buttonRes, SIGNAL(clicked()), this, SLOT(HANDLER_RESBTN_PRESSED()));
        QObject::connect(buttonDel, SIGNAL(clicked()), this, SLOT(HANDLER_DELBTN_PRESSED()));
    }
    this->show();
}

TrashDialog::~TrashDialog()
{
    delete ui;
}

void TrashDialog::HANDLER_RESBTN_PRESSED()
{
    QWidget *clickedWidget = qobject_cast<QWidget *>(sender()->parent());
    QListWidgetItem *runningItem;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        runningItem = ui->listWidget->item(i);
        QWidget *widget = ui->listWidget->itemWidget(runningItem);
        if (clickedWidget == widget) {
            ui->listWidget->setCurrentItem(runningItem);
            break;
        }
    }

    Trash::getInstance()->restore(dynamic_cast<QListWidgetItemWithNote*>(runningItem)->getN());
    delete runningItem;
}

void TrashDialog::HANDLER_DELBTN_PRESSED()
{
    QWidget *clickedWidget = qobject_cast<QWidget *>(sender()->parent());
    QListWidgetItem *runningItem;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        runningItem = ui->listWidget->item(i);
        QWidget *widget = ui->listWidget->itemWidget(runningItem);
        if (clickedWidget == widget) {
            ui->listWidget->setCurrentItem(runningItem);
            break;
        }
    }

    Trash::getInstance()->remove(dynamic_cast<QListWidgetItemWithNote*>(runningItem)->getN());
    delete runningItem;
}
