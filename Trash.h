#ifndef TRASH_H
#define TRASH_H

#include "Document.h"
#include <QSet>

class DeletedNote;

typedef QSet<Document*>::const_iterator docSetIt;
typedef QSet<DeletedNote*>::const_iterator noteSetIt;

/*!
 * \brief The DeletedNote class Une classe qui englobe une note.
 * Dans la corbeille, nous aurons ainsi un ensembles des DeletedNotes.
 * La corbeille va recycle() une note et la transformaer en DeletedNote, tout en gardant les relations entre une note et les documents qui lui contiennent
 * Lors de la restauration d'une note. DeletedNote sera transforme en Note et en suite, retourne dans la liste des Notes. Les associations Docuemnt/Note sont egalement restaures.
 * On fait une composition au lieu de heritage car on veut etre sur qu'un deletedNote ne soit pas traite comme les autres notes
 * Toutes les methodes de cette classes sont privee, on declarer pour cela les classes trash et trashDialog comme amie.
 * Ceci permet d'assurer que seuls les objet de la classe Trash et TrashDialog peuvent manipuler avec deletedNote.
 */
class DeletedNote{
    Note *n;
    QSet<Document*> wasInDocuments;

    /*!
     * \brief getNote
     * \return retourne le Note englobee dans deletedNote.
     */
    Note *getNote() const;
    void setNote(Note *value);
    /*!
     * \brief begin
     * \return retourne un iterateur sur les \link<wasInDocuments> ceci est utilise lors de la restauration du note.
     */
    docSetIt begin(){return wasInDocuments.begin();}
    docSetIt end(){return wasInDocuments.end();}
    QSet<Document *> getWasInDocuments() const;
    void setWasInDocuments(const QSet<Document *> &value);
    DeletedNote(Note *n);
    ~DeletedNote();

public:
    /*!
     * Ceci permet d'assurer que seuls les objet de la classe Trash et TrashDialog peuvent manipuler avec deletedNote.
     */
    friend class Trash;
    /*!
     * Ceci permet d'assurer que seuls les objet de la classe Trash et TrashDialog peuvent manipuler avec deletedNote.
     */
    friend class TrashDialog;
};

/*!
 * \brief The Trash class Cette classe [singlton] propose trois fonctionalite: recycle(), restoire(), et remove().
 */
class Trash
{
    QSet<DeletedNote*> deletedNotes;

    static Trash* instance;

    Trash& operator=(const Trash& t);
    Trash(const Trash& t);

    Trash();
public:
    static Trash * getInstance();
    static void releaseInstance();

    /*!
     * \brief dissasocie note n avec tous les documents. Mettre deleted a true. ensuite envelopper cette Note dans une deletedNote.
     * \param n
     */
    void recycle(Note *n);
    /*!
     * \brief restore On restaurer une deletedNote n. On restaure egalement les relations entre n et les Documents qui le contenaient avant la suppresions.
     * a condition que ces documents existent toujours.
     * \param n
     */
    void restore(DeletedNote *n);
    /*!
     * \brief remove supprmer definitivement la note n. Suppression du fichier.
     * \param n
     */
    void remove(DeletedNote *n);

    noteSetIt begin(){return deletedNotes.begin();}
    noteSetIt end(){return deletedNotes.end();}
};

#endif // TRASH_H
