#include "NoteTypeSignalAction.h"
#include "NoteFactory.h"
#include <QSignalMapper>

NoteTypeSignalAction::NoteTypeSignalAction(NoteType type, const QString& label, QObject *parent) :
    QAction(label, parent), nType(type)
{
    QSignalMapper* signalMapper = new QSignalMapper(this);

    connect(this, SIGNAL(triggered()), signalMapper, SLOT(map()));
    signalMapper->setMapping(this, (int)nType);

    connect(signalMapper, SIGNAL(mapped(const int)),
                 this, SIGNAL(triggeredWithId(int)));
}


ExportTypeSignalAction::ExportTypeSignalAction(ExportType type, const QString &label, QObject *parent) :
    QAction(label, parent), nType(type)
{
    QSignalMapper* signalMapper = new QSignalMapper(this);

    connect(this, SIGNAL(triggered()), signalMapper, SLOT(map()));
    signalMapper->setMapping(this, (int)nType);

    connect(signalMapper, SIGNAL(mapped(const int)),
                 this, SIGNAL(triggeredWithId(int)));
}
