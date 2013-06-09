#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include "Tag.h"
#include <QObject>
#include <QSet>

class Note;
class Tag;

typedef QSet<Tag* >::iterator tagSetIt;

/*!
 * \brief The TagManager class Cette classe sert comme intermediare entre les notes et les tags. [Singleton]
 */
class TagManager // singleton
{
    TagManager();
    ~TagManager();
    TagManager(const TagManager& tag);
    TagManager& operator=(const TagManager& t);

    static TagManager* instance;

    /*!
     * \brief Tags L'ensemble de tous les Tags.
     * Tous les Tags sont construits par le TagManager.
     */
    QSet<Tag*> Tags;

    /*!
     * \brief createTag Creation d'un nouveau tag avec le nom n
     * \param n
     * \return un pointeur sur un nouveau tag.
     */
    Tag* createTag(const QString &n);

public:
    void addTag(Tag *t) {Tags<<t;}
    static TagManager& getInstance();
    static void libereInstance();
    QSet<Tag *> getTags();

    /*!
     * \brief removeTag Disassocie mutuellement le tag t et tous les notes associes a ce tag.
     * \param t
     */
    void removeTag(Tag* t);
    /*!
     * \brief getTagforNote recuperer tous les tags qui sont attache a note.
     * \param note
     * \return Un ensemble des tags associe a note.
     */
    const QSet<Tag *>& getTagforNote(Note* note);
    /*!
     * \brief getNoteforTag recuperer tous les notes qui sont attache a tag.
     * \param tag
     * \return Un ensemble des notes associe a tag.
     */
    QSet<Note*>& getNotesforTag(Tag *tag);
    /*!
     * \brief addTagToNote Ajouter mutuellement l'association entre un tag et une note.
     * \param tag
     * \param note
     */
    void addTagToNote(Tag *tag, Note *note);
    /*!
     * \brief removeTagForNote elever mutuellement l'association entre un tag et une note
     * \param tag
     * \param note
     */
    void removeTagForNote(Tag* tag, Note* note);
    /*!
     * \brief getTag recuperer un tag a partir de sont nom newtag
     * \param newtag
     * \return retourne un pointeur sur un tag existant qui porte le meme nom ou bien en creer un s'il n'existe pas encore.
     */
    Tag* getTag(const QString& newtag);

    /*!
     * \brief begin l'adaptation de QSet<Tag*>
     * \return retourne un iterateur sur le premier Tag existant.
     */
    tagSetIt begin(){return Tags.begin();}
    /*!
     * \brief end l'adaptation de QSet<Tag*>
     * \return retourne un iterateur sur l'apres dernier Tag existant.
     */
    tagSetIt end(){return Tags.end();}
};

#endif // TAGMANAGER_H
