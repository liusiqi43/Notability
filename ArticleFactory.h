#ifndef ARTICLEFACTORY_H
#define ARTICLEFACTORY_H

#include "NoteFactory.h"
#include "Article.h"

/*!
 * \brief The ArticleFactory class Cette classe genere les \link <Article> a partir d'un chemin existant, ou bien generer un nouveau Article.
 */
class ArticleFactory : public NoteFactory
{
public:
    Article* buildNewNote();
    Article* buildNote(const QString &path);

    /*!
     * \brief getFolder Cette methode virtuelle genere le bon repertoire pour les notes generes.
     * \return ART/ dans ce cas la. Ceci est uniquement utile pour organiser les fichiers pour les humains
     */
    QString getFolder();

    /*!
     * \brief getExtension Cette methode virtuelle genere le bon extension pour les \link <Articles>.
     * \return .art. Cette extension sera utilise lors de l'ouverture du fichier \deprecated {L'ouverture du fichier est supprime car on prefere cache cette fonctionalite pour deboggage. En fait, l'utilisateurs ne connais que les titres du notes, mais pas l'id du fichier.}
     */
    QString getExtension();
};

#endif // ARTICLEFACTORY_H
