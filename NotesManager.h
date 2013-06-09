#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QList>
#include <QMap>
#include "Document.h"
#include "NoteFactory.h"
#include "ExportStrategy.h"

class Note;
class ImageNote;


typedef QList<Note *>::const_iterator nListIt;
typedef QSet<Document *>::const_iterator dSetIt;

class NotesManager {
private:
    // Used for fast access to a list of all opened documents
    QSet<Document *> DocumentsContainer;
    /*!
     * \brief mapper Ceci est utilise pour mapper l'acien chemin avec le nouveau chemin genere lors de la duplication des notes au cours du changement de l'espace de travail. Ceci a pour l'effet d'assurer que l'on ne duplique qu'une seule fois la meme note car la meme note peut se trouve dans les different documents.
     * Ceci est "lazily" intialise ce qui fait qu'il n'occupe quasiment pas de memoire si utilisateur n'utilise pas cette fonctionalite
     */
    QMultiMap<QString, QString> *mapper;

    /*!
     * \brief rootDocument document qui sert comme la racine de tous les notes. Ceci est necessaire pour gere l'hierarchie de l'ensemble des notes.
     */
    Document *rootDocument;

    /*!
     * \brief addNote QSet will deduplicate automatically, as we have an ID attribute in Note.
     * If Note does not have an ID attribute, we can only use QSet<Note> as it will compares its address and hash.
     * \param a
     */
    void addNote(Note* a);

    NotesManager();
    ~NotesManager();

    NotesManager(const NotesManager&); // non defini mais prive pour empecher la duplication
    NotesManager& operator=(const NotesManager&); // meme chose
    static NotesManager* instance; // pointeur sur l'unique instance

    /*!
     * \brief saveDocument On sauvegarde un document recursivement en prenant compte de tous les notes aggreges par ce document.
     * \param d
     */
    void saveDocument(Document& d);

public:
    /*!
     * \brief removeNote Ceci va enleve \link<a> depuis le \link<rootDocument>. Cette suppression est mutuelle. cf \link<Document>
     * \param a
     */
    void removeNote(Note* a);
    /*!
     * \brief strategies Un Map de tous les exportStrategies disponibles
     */
    QMap<ExportType, ExportStrategy*>* strategies;
    /*!
     * \brief factories Un Map de tous les NotesFactory disponibles
     */
    QMap<NoteType, NoteFactory*>* factories;
    /*!
     * \brief getInstance NotesManager est un singleton
     * \return unique instance de NotesManager.
     */
    static NotesManager& getInstance();
    static void libererInstance();
    Note& getNote(const QString& filename);
    Note& getNoteClone(const Note &note);
    Note& getNewNote(NoteType type);
    void saveNote(Note& a);

    nListIt begin(){return rootDocument->begin();}
    nListIt end(){return rootDocument->end();}

    /*!
     * \brief beginDocumentContainer
     * \return un iterator sur le premier Document qui est charge dans le programme. Utile pour recuperer tous les documents disponbiles.
     */
    dSetIt beginDocumentContainer(){return DocumentsContainer.begin();}
    dSetIt endDocumentContainer(){return DocumentsContainer.end();}
    Document *getRootDocument() const;
    /*!
     * \brief setRootDocument Cette methode est principalement utilise lors du changement de l'espace de travail.
     * \param value
     */
    void setRootDocument(Document *value);
};

#endif // NOTESMANAGER_H
