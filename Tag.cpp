#include <QDebug>
#include "Tag.h"

Tag::Tag(const QString& n): name(n)
{
    assocs.clear();
}


QString Tag::getName() const
{
    return name;
}

void Tag::setName(const QString &value)
{
    qDebug() << "Setting tag: " << name << " to " << value;
    name = value;
}

void Tag::addNote(Note* n)
{
    assocs.insert(n);
}

void Tag::removeNote(Note *n)
{
    assocs.remove(n);
}

