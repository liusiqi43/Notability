#include "QListWidgetItemWithItemAndNote.h"

#include "Trash.h"
#include "mainwindow.h"

QListWidgetItemWithNote::QListWidgetItemWithNote(DeletedNote* note)
    :QListWidgetItem(), n(note)
{}

DeletedNote *QListWidgetItemWithNote::getN() const
{
    return n;
}

void QListWidgetItemWithNote::setN(DeletedNote *value)
{
    n = value;
}
