#ifndef QLISTWIDGETITEMWITHITEMANDNOTE_H
#define QLISTWIDGETITEMWITHITEMANDNOTE_H

#include <QObject>
#include <QListWidgetItem>

class DeletedNote;

/*!
 * \brief The QListWidgetItemWithNote class Adaptation de QListWidgetItem, qui associe un widget avec un \link<DeletedNote>
 */
class QListWidgetItemWithNote : public QListWidgetItem
{
    DeletedNote *n;
public:
    explicit QListWidgetItemWithNote(DeletedNote *note);
    DeletedNote *getN() const;
    void setN(DeletedNote *value);
};

#endif // QLISTWIDGETITEMWITHITEMANDNOTE_H
