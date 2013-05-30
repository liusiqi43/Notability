#ifndef TAG_H
#define TAG_H

#include <QObject>

class Tag
{
    QString name;

public:
    Tag(const QString& n);
    QString getName() { return name; }
};

#endif // TAG_H
