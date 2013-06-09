#ifndef NOTETYPESIGNALACTION_H
#define NOTETYPESIGNALACTION_H

#include <QAction>
#include "NoteFactory.h"
#include "ExportStrategy.h"

/*!
 * \brief The NoteTypeSignalAction class Cette class herite de QAction qui permet d'envoie un signal qui signifie le type de note associe a cette action.
 * Ceci permet d'utilise un seul Slot pour gerer un ensembles des actions (ex. NewArticleAction, NewDocumentActions etc...).
 * Ici, nous avons utilise un \link<QSignalMapper> pour rediriger la signal.
 */
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

/*!
 * \brief The ExportTypeSignalAction class Cette class herite de QAction qui permet d'envoie un signal qui signifie le type de export associe a cette action.
 * Ceci permet d'utilise un seul Slot pour gerer un ensembles des actions (ex. ExportHtml, ExportTex etc...).
 * Ici, nous avons utilise un \link<QSignalMapper> pour rediriger la signal.
 */
class ExportTypeSignalAction : public QAction
{
    Q_OBJECT
    ExportType nType;
public:
    explicit ExportTypeSignalAction(ExportType type, const QString& label, QObject *parent);
signals:
    void triggeredWithId(const int id);
public slots:

};


#endif // NOTETYPESIGNALACTION_H
