#ifndef QLISTWIDGETITEMCHECKTAG_H
#define QLISTWIDGETITEMCHECKTAG_H
#include <QListWidgetItem>

class Tag;

class ListWidgetItemCheckTag : public QListWidgetItem
{
    Tag* tag;
public:
    ListWidgetItemCheckTag(const QString & name, Tag * t, QListWidget * parent = 0, int type = Type):
        QListWidgetItem(name, parent, type), tag(t) {}

    Tag * getTag() const;
};

#endif // QLISTWIDGETITEMCHECKTAG_H
