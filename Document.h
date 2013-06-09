#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Note.h"
#include "DocumentEditor.h"

typedef QList<Note *>::const_iterator nListIt;

/*!
 * \brief The Document class Cette classe herite de Note.
 * Cette classe represente un type de Note special qui permet d'aggreger plusieurs Note (y compris les autres documents)
 */
class Document: public Note{
    /*!
     * \brief notes Une liste des Notes aggreges.
     */
    QList<Note *> notes;

public:
    Document(const QString& path);
    Document(const QString& path, const QString& ti);
    ~Document();

    /*!
     * \brief begin, ici, la classe Document adapte la classe QList de facons a faciliter le parcours de tous les notes aggreges.
     * \return un iterator sur le premier note contenu dans le document courant
     */
    nListIt begin() const;

    /*!
     * \brief end
     * \return un iterator sur apres dernier note (fictif) contenu dans le document courant
     */
    nListIt end() const;

    /*!
     * \brief contains Adaptation de QList
     * \param n Note a tester
     * \return True si ce Document contient \link<n> False sinon
     */
    bool contains(Note *n) const;

    /*!
     * \brief addNote Ajouter un Note dans un document.
     * Si cette Note est a son tour un document, nous allons tester s'il existe une inclusion circulaire entre les deux documents. Ce qui est absolument ilogique
     * Si tout va bien, le note sera ajoute dans le \link<notes> et ce document sera aussi ajoute dans le \link <inDocuments> du note.
     * \param note
     */
    void addNote(Note *note) throw (NotesException);

    /*!
     * \brief count
     * \return le nombre de notes aggrege dans ce documents. Adaptation du QList
     */
    int count() const;

    /*!
     * \brief removeNote enleve le note depuis ce Document.
     * \param note le note a enlever
     * \param twoway true si on veux une dissociation mutuelle, false si on peut seulement enlever une note depuis ce document mais pas enveler ce document depuis le inDocuments de note
     */
    void removeNote(Note *note, bool twoway = true);

    /*!
     * \brief find chercher recursivement dans ce document si une Note identifie par son chemin est aggrege dans ce document
     * \param filepath l'identifiant du note
     * \return true si une note avec filePath est aggrege dans ce document, false sinon.
     */
    Note* find(const QString& filepath);

    /*!
     * \brief createEditor genere un \link<DocumentEditor>. Cette methode va recursivement appeler les createEditor() des notes aggreges, et puis les ajouter dans sont contentLayout.
     * \return
     */
    DocumentEditor *createEditor(){return new DocumentEditor(this);}

    /*!
     * \brief exportNote Cette methode genere une representation textuelle du Document. Elle va recursivement appeler la methode exportNote de toutes les notes aggreges.
     * \param es ExportStrategy choisie
     * \param level Le niveau d'indentation
     * \return
     */
    QString exportNote(const ExportStrategy *es, unsigned int level = 0);

    /*!
     * \brief The DepthFirstIterator cette classe donne une iterateur profondeur d'abord. C'est a dire en iterant sur ce iterateur, on va pouvoir parcourir l'ensemble des notes aggreges directement ou indrectement dans ce document
     */
    class DepthFirstIterator{
        /*!
         * \brief fringe Les noeuds restant a parcourir
         */
        QList<Note*> fringe;
        /*!
         * \brief explored Les noeuds deja parcouru (pour traiter le cas ou la meme note est aggrege plusieurs fois dans un meme document, car elle peut etre aggrege dans un sous document de ce document)
         */
        QSet<Note*> explored;
    public:
        // prefix
        /*!
         * \brief hasNext JavaStyle Iterator while(hasNext()) {next();}
         * \return
         */
        bool hasNext() const;
        Note *next();
        DepthFirstIterator(Document * const);

    };

    /**
     * @brief beginDFIterator
     * @return Un iterator sur le document lui meme.
     */
    DepthFirstIterator &beginDFIterator();
};


#endif // DOCUMENT_H
