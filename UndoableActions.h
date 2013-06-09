#ifndef UNDOABLEACTIONS_H
#define UNDOABLEACTIONS_H

#include <QUndoCommand>
#include "ListWidgetItemCheckTag.h"

class Note;

/*!
 * \brief The AddNewTagCmd class sous classe de QUndoCommand.
 * Le principe est de donner la definition de l'action et son inverse. A chaque fois, on push l'action sur un \link<QUndoStack> pour pouvoir ensuite
 * revenir arriere en appelant la methode undo definit ici. On definit setText() dans la constructeur pour donner une represetation texteulle du command, qui sera affiche dans l'historique.
 * Nous n'avons pas eu le temps de remplacer toutes les actions par les undoablecommands. Ici, on a realise un ensembles des actions concernant la manipulation des Tags.
 * On pourrait envisager de l'impementer pour toutes les autres actions dans le futur.
 */
class AddNewTagCmd : public QUndoCommand
{
public:
    AddNewTagCmd(QListWidget* l, QUndoCommand *parent = 0);

    /*!
     * \brief undo On surcharger cette methode. Pour donner la definition de l'action inverse du command.
     */
    void undo();
    /*!
     * \brief redo On surcharger cette methode. Pour donner la definition de l'action du command.
     */
    void redo();

private:
    ListWidgetItemCheckTag* item;
    QListWidget *list;
    Tag *tag;
};

/*!
 * \brief The RemoveCurrentTagCmd class sous classe de QUndoCommand.
 * Le principe est de donner la definition de l'action et son inverse. A chaque fois, on push l'action sur un \link<QUndoStack> pour pouvoir ensuite
 * revenir arriere en appelant la methode undo definit ici. On definit setText() dans la constructeur pour donner une represetation texteulle du command, qui sera affiche dans l'historique.
 * Nous n'avons pas eu le temps de remplacer toutes les actions par les undoablecommands. Ici, on a realise un ensembles des actions concernant la manipulation des Tags.
 * On pourrait envisager de l'impementer pour toutes les autres actions dans le futur.
 */
class RemoveCurrentTagCmd : public QUndoCommand
{
public:
    RemoveCurrentTagCmd(QListWidget* l, ListWidgetItemCheckTag *t, QUndoCommand *parent = 0);

    void undo();
    void redo();

private:
    ListWidgetItemCheckTag *item;
    Tag *tag;
    QSet<Note*> assos;
    QListWidget *list;
    Qt::CheckState checkstate;
};


/*!
 * \brief The EditCurrentTagCmd class sous classe de QUndoCommand.
 * Le principe est de donner la definition de l'action et son inverse. A chaque fois, on push l'action sur un \link<QUndoStack> pour pouvoir ensuite
 * revenir arriere en appelant la methode undo definit ici. On definit setText() dans la constructeur pour donner une represetation texteulle du command, qui sera affiche dans l'historique.
 * Nous n'avons pas eu le temps de remplacer toutes les actions par les undoablecommands. Ici, on a realise un ensembles des actions concernant la manipulation des Tags.
 * On pourrait envisager de l'impementer pour toutes les autres actions dans le futur.
 */
class EditCurrentTagCmd : public QUndoCommand
{
    QString oldName, newName;
    Tag *tag;
    QListWidget *list;
    static bool first;
public:
    EditCurrentTagCmd(ListWidgetItemCheckTag *i, QListWidget *l, QUndoCommand *parent = 0);

    void undo();
    void redo();
};

#endif // UNDOABLEACTIONS_H
