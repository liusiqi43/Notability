#ifndef QLISTWIDGETITEMWITHITEMANDNOTE_H
#define QLISTWIDGETITEMWITHITEMANDNOTE_H

#include <QObject>
#include <QListWidgetItem>

class DeletedNote;

class QListWidgetItemWithNote : public QListWidgetItem, public QObject
{
    DeletedNote *n;
public:
    explicit QListWidgetItemWithNote(DeletedNote *note);
    DeletedNote *getN() const;
    void setN(DeletedNote *value);
};

#endif // QLISTWIDGETITEMWITHITEMANDNOTE_H
