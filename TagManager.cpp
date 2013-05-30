#include "TagManager.h"
#include "Notes.h"

//méthodes pour le singleton
TagManager* TagManager::instance=0;

TagManager::TagManager()
{
    Tags.clear();
}

TagManager::~TagManager()
{
    Tags.clear();
}


TagManager& TagManager::getInstance()
{
    if(!instance)
    {
        instance= new TagManager;
    }
}

void TagManager::libereInstance()
{
    if(instance)
    {
        delete instance;
        instance=0;
    }
}

//on passe au chose sérieuse
QSet<Tag*> TagManager::getTags()
{
    return Tags;
}

void TagManager::createTag(const QString& n)
{
    Tag *t = new Tag(n);
    Tags << t;
}

void TagManager::addTagToNote(Tag* tag, Note* note)
{
    tag->addNote(note);
}

void TagManager::removeTag(Tag* t)
{
    Tags.remove(t);
}

QSet<Note *> TagManager::getNoteforTag(Tag* tag)
{
    tag->getAssocs();
}

QSet<Tag*> TagManager::getTagforNote(Note *note)
{
    QSet<Tag*> res;
    for(nSetIt it = begin(); it != end(); it++){
        if((**it).getAssocs().contains(note))
        {
            res<<(*it);
        }
    }
    return res;
}

void TagManager::removeTagToNote(Tag *tag, Note *note)
{
    for(nSetIt it = begin(); it != end(); it++){
        if((*it)==tag && (**it).getAssocs().contains(note))
        {
            (**it).getAssocs().remove(note);
        }
    }
}
