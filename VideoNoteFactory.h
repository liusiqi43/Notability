#ifndef VIDEONOTEFACTORY_H
#define VIDEONOTEFACTORY_H

#include "NoteFactory.h"
#include "VideoNote.h"

/*!
 * \brief The VideoNoteFactory class Cette classe genere des notes de type VideoNote a partir d'un fichier ou a partir du zero
 */
class VideoNoteFactory : public NoteFactory
{
public:
    VideoNote* buildNewNote();
    VideoNote* buildNote(const QString &path);

    /*!
     * \brief getFolder Cette methode virtuelle genere le bon repertoire pour les notes generes.
     * \return VID/ dans ce cas la. Ceci est uniquement utile pour organiser les fichiers pour les humains
     */
    QString getFolder();

    /*!
     * \brief getExtension Cette methode virtuelle genere le bon extension pour les \link<Articles>.
     * \return .vid. Cette extension sera utilise lors de l'ouverture du fichier \deprecated {L'ouverture du fichier est supprime car on prefere cache cette fonctionalite pour deboggage. En fait, l'utilisateurs ne connais que les titres du notes, mais pas l'id du fichier.}
     */
    QString getExtension();
};

#endif // VIDEONOTEFACTORY_H
