#ifndef AUDIONOTEFACTORY_H
#define AUDIONOTEFACTORY_H

#include "NoteFactory.h"
#include "AudioNote.h"


/*!
 * \brief The AudioNoteFactory class Cette classe genere les \link <AudioNote> a partir d'un fichier existant ou genere un nouveau fichier.
 */
class AudioNoteFactory : public NoteFactory
{
public:
    AudioNote* buildNewNote();
    AudioNote* buildNote(const QString &path);

    /*!
     * \brief getFolder Cette methode virtuelle genere le bon repertoire pour les notes generes.
     * \return AUD/ dans ce cas la. Ceci est uniquement utile pour organiser les fichiers pour les humains
     */
    QString getFolder();

    /*!
     * \brief getExtension Cette methode virtuelle genere le bon extension pour les \link <AudioNote>.
     * \return .aud. Cette extension sera utilise lors de l'ouverture du fichier \deprecated {L'ouverture du fichier est supprime car on prefere cache cette fonctionalite pour deboggage. En fait, l'utilisateurs ne connais que les titres du notes, mais pas l'id du fichier.}
     */
    QString getExtension();
};
#endif // AUDIONOTEFACTORY_H
