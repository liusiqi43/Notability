#ifndef UNDOABLEACTIONS_H
#define UNDOABLEACTIONS_H

#include <QUndoCommand>
#include <ListWidgetItemCheckTag.h>

class Note;

class AddNewTagCmd : public QUndoCommand
{
public:
    AddNewTagCmd(QListWidget* l, QUndoCommand *parent = 0);
//    ~AddNewTagCmd();

    void undo();
    void redo();

private:
    ListWidgetItemCheckTag* item;
    QListWidget *list;
    Tag *tag;
};

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
