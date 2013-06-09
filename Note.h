#ifndef NOTE_H
#define NOTE_H

#include <QSet>
#include <QString>

#include "Editor.h"
#include "NotesException.h"
#include "NoteFactory.h"


class Document;
class ExportStrategy;
class Document;
class Tag;
typedef QList<Note *>::const_iterator nListIt;

/*!
 * \brief The Note class La classe de base pour tous les Notes.
 */
class Note{
    QString title;
    /*!
     * \brief filePath Le chemin du fichier est utilise comme identifiant unique du Note.
     */
    QString filePath;
    /*!
     * \brief tags La liste des tags seront enreigistre comme une propriete des Notes. Au lancement du programme, tous les tags associes aux notes existants seront charge dans le programme.
     *
     * Ceci permet un acces directe aux tags associe aux notes. cf \link<Tag>
     */
    QSet<Tag*> tags;

    /*!
     * the Editor associated. Ceci permet une association etroite entre un objet Note et son editor. Association est assuree au moment du creation de editeur
     */
    Editor* editor;

    /*!
     * All documents that directly contains this note. For fast access in editors
     */
    QSet<Document*> inDocuments;
    bool modified;

    /*!
     * \brief deleted Cet attribut est manipule uniquement par le singleton \link<Trash>.
     */
    bool deleted;

public:
    /*!
     * \brief type Ce type est determine au moment de la construction de Note. Ceci nous permet d'eviter les exceptions non necessaire lors de la duplication des notes (cf. NoteFactory, buildNoteCopy etc...)
     */
    NoteType type;
    Note(const QString &path);
    Note(const QString &path, const QString& ti);

    virtual ~Note();

    const QSet<Tag*>& getTags() const{
        return tags;
    }

    void setTags(const QSet<Tag*> value) {this->setModified(true); this->tags = value;}
    void addTag(Tag *tag) {this->setModified(true); tags << tag;}
    void removeTag(Tag *tag) {this->setModified(true); tags.remove(tag);}

    /*!
     * \brief addNote Purement pour facilier a hirarchiser les Notes dans nm.Et puis ca sert a visualiser cette hirarchie dans QTreeView.
     */
    virtual void addNote(Note *){throw NotesException("Should not happen! addNote called for non Document object.");}

    /*!
     * \brief operator == Les notes sont identifie a partir de leurs chemin.
     * \param other
     * \return
     */
    bool operator==(const Note& other);

    const QString &getTitle() const;
    void setTitle(const QString &t);

    const QString &getFilePath() const;
    void setFilePath(const QString &p);

    void setModified(bool b);
    bool isModified() const;

    void setDeleted(bool b);
    bool isDeleted() const;

    /*!
     * \brief createAndAttachEditor Methode template qui fait appel aux createEditor() des classes filles et puis associe l'editeur construite a note lui meme.
     * \return
     */
    Editor *createAndAttachEditor();
    /*!
     * \brief createEditor Methode virtuelle pure definie dans les classes filles
     * \return
     */
    virtual Editor *createEditor() = 0;

    /*!
     * \brief createEditor Methode virtuelle pure definie dans les classes filles
     * \return
     */
    virtual QString exportNote(const ExportStrategy *es, unsigned int level = 0) = 0;

    /*!
     * \brief isDocument \deprecated{ Methode prevu pour distinguer les documents. Distinguer le type du note par rapport a son type dans le futur}
     * \return
     */
    bool isDocument() const;

    /*!
     * \brief begin retourne 0 si Note n'est pas du type Document. Retourne un iterator sur le premier Note contenue dans note s'il est un document
     * \return
     */
    nListIt begin() const;

    /*!
     * \brief begin retourne 0 si Note n'est pas du type Document. Retourne un iterator sur l'apres dernier Note contenue dans note s'il est un document
     * \return
     */
    nListIt end() const;

    Editor *getEditor() const;
    void setEditor(Editor *value);

    void addToDocument(Document* doc);
    void removeFromDocument(Document *doc);
    bool belongs(Document *doc);

    /*!
     * \brief beginInDoc
     * \return Retourner un iterateur sur le premier element dans la liste des document ou se trouve ce note.
     */
    QSet<Document *>::const_iterator beginInDoc(){return inDocuments.begin();}
    /*!
     * \brief beginInDoc
     * \return Retourner un iterateur sur apres dernier element dans la liste des document ou se trouve ce note.
     */
    QSet<Document *>::const_iterator endInDoc(){return inDocuments.end();}
    QSet<Document *> getInDocuments() const;
    void setInDocuments(const QSet<Document *> &value);

    /*!
     * \brief resetInDocuments Methode raccourci utilise principalement pour disassocie le note et les documents qui englobe cette note.
     */
    void resetInDocuments(){inDocuments.clear();}
};



#endif

