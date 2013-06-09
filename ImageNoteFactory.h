#ifndef IMAGENOTEFACTORY_H
#define IMAGENOTEFACTORY_H

#include "NoteFactory.h"
#include "ImageNote.h"

/*!
 * \brief The ImageNoteFactory class Cette classe genere des note de type \link<ImageNote> a partir d'un fichier existant ou a partir du zero
 */
class ImageNoteFactory : public NoteFactory
{
public:
    ImageNote* buildNewNote();
    ImageNote* buildNote(const QString &path);

    /*!
     * \brief getFolder Cette methode virtuelle genere le bon repertoire pour les notes generes.
     * \return IMG/ dans ce cas la. Ceci est uniquement utile pour organiser les fichiers pour les humains
     */
    QString getFolder();

    /*!
     * \brief getExtension Cette methode virtuelle genere le bon extension pour les \link<Articles>.
     * \return .img. Cette extension sera utilise lors de l'ouverture du fichier \deprecated {L'ouverture du fichier est supprime car on prefere cache cette fonctionalite pour deboggage. En fait, l'utilisateurs ne connais que les titres du notes, mais pas l'id du fichier.}
     */
    QString getExtension();
};


#endif // IMAGENOTEFACTORY_H
