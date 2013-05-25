#ifndef NOTETYPESIGNALACTION_H
#define NOTETYPESIGNALACTION_H

#include <QAction>
#include "NoteFactory.h"


class NoteTypeSignalAction : public QAction
{
    Q_OBJECT
    NoteType nType;
public:
    explicit NoteTypeSignalAction(NoteType type, const QString& label, QObject *parent);
signals:
    void triggeredWithId(const int id);
public slots:
    
};

#endif // NOTETYPESIGNALACTION_H
