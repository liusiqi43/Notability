#ifndef DOCUMENTEDITOR_H
#define DOCUMENTEDITOR_H

#include "Editor.h"
#include <QToolBar>
class Document;

/*!
 * \brief The DocumentEditor class Cette classe herite de la superclass Editor, qui s'occupe de configuration genenrale des editors. Cette classe ne s'occupe que de la specialisation de la classe.
 */
class DocumentEditor : public Editor
{
    Q_OBJECT
    QToolBar * toolBar;
public:
    /*!
     * \brief DocumentEditor Cette methode creer et appele la methode createAndAttachEditor() de toutes les notes directement ou indirectement aggregees
     * \param doc Le doc racine du editeur
     * \param parent
     */
    explicit DocumentEditor(Document* doc, QWidget *parent=0);

signals:

public slots:
    void BACKEND_SET_CONTENT();
    void UI_NEW_NOTE_EDITOR(const int type);
};

#endif // DOCUMENTEDITOR_H
