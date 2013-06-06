#include "TagManager.h"
#include "Tag.h"
#include <QSet>
#include "Note.h"
#include <QDebug>


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

    return *instance;

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

Tag* TagManager::createTag(const QString& n)
{
    Tag *t = new Tag(n);
    Tags << t;
    return t;
}

void TagManager::addTagToNote(Tag* tag, Note* note)
{
    note->addTag(tag);
    tag->addNote(note);
}

void TagManager::removeTag(Tag* t)
{

    for(QSet<Note*>::iterator it = t->getAssocs().begin(); it != t->getAssocs().end(); it++)
    {
        (*it)->removeTag(t);
    }
    t->reset();
    Tags.remove(t);
}

QSet<Note *>& TagManager::getNotesforTag(Tag* tag)
{
    return tag->getAssocs();
}

const QSet<Tag*>& TagManager::getTagforNote(Note *note)
{
    return note->getTags();
}

void TagManager::removeTagForNote(Tag *tag, Note *note)
{
    tag->removeNote(note);
    note->removeTag(tag);
}

Tag* TagManager::getTag(const QString& newtag)
{
    for(tagSetIt it= begin(); it != end(); it++)
    {
        if((*it)->getName()==newtag) {
            qDebug()<<"Gotcha!";
            return *it;
        }
    }
    qDebug()<<"created Tag: " << newtag;
    return createTag(newtag);
}

