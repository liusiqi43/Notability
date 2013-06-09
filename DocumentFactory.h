#ifndef DOCUMENTFACTORY_H
#define DOCUMENTFACTORY_H

#include "NoteFactory.h"
#include "Document.h"


/*!
 * \brief The DocumentFactory class Cette classe genere les notes de type Document a partir d'un fichier ou bien a partir du zero.
 */
class DocumentFactory : public NoteFactory
{
public:
    Document* buildNewNote();
    Document* buildNote(const QString &path);
    /*!
     * \brief getFolder Cette methode virtuelle genere le bon repertoire pour les notes generes.
     * \return DOC/ dans ce cas la. Ceci est uniquement utile pour organiser les fichiers pour les humains
     */
    QString getFolder();

    /*!
     * \brief getExtension Cette methode virtuelle genere le bon extension pour les \link <Document>.
     * \return .doc. Cette extension sera utilise lors de l'ouverture du fichier \deprecated {L'ouverture du fichier est supprime car on prefere cache cette fonctionalite pour deboggage. En fait, l'utilisateurs ne connais que les titres du notes, mais pas l'id du fichier.}
     */
    QString getExtension();
};

#endif // DOCUMENTFACTORY_H
