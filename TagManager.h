#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include "Tag.h"
#include <QObject>
#include <QSet>

class Note;
class Tag;

typedef QSet<Tag* >::iterator tagSetIt;

class TagManager // singleton
{
    TagManager();
    ~TagManager();
    TagManager(const TagManager& tag);
    TagManager& operator=(const TagManager& t);

    static TagManager* instance;

    QSet<Tag*> Tags;


public:

    static TagManager& getInstance();
    static void libereInstance();
    QSet<Tag *> getTags();
    void createTag(const QString &n);
    void removeTag(Tag* t);
    QSet<Tag *>& getTagforNote(Note* note);
    QSet<Note*>& getNotesforTag(Tag *tag);
    void addTagToNote(Tag *tag, Note *note);
    void removeTagForNote(Tag* tag, Note* note);
    Tag* getTag(const QString& newtag);

    tagSetIt begin(){return Tags.begin();}
    tagSetIt end(){return Tags.end();}
};

#endif // TAGMANAGER_H
