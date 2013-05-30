#include "TagManager.h"
#include "Notes.h"

//méthodes pour le singleton
TagManager* TagManager::instance=0;

TagManager::TagManager(): nbAssoc(0), associations(new TagNote)
{
    Tags.clear();
}

TagManager::~TagManager()
{
    Tags.clear();
    for(unsigned int j=0; j<nbAssoc-1; j++) delete associations[j];
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
    Tag t(n);
    Tags<<&t;
}

void TagManager::addTagToNote(Tag* tag, Note* note)
{
    associations[nbAssoc]->note=note;
    associations[nbAssoc]->tag=tag;
    nbAssoc++;
}

void TagManager::removeTag(Tag* t)
{
    Tags.remove(t); // supprime le tag
}

Note** TagManager::getNoteforTag(Tag* tag)
{
    Note** res=NULL;
    unsigned int nb=0;
    for(unsigned int i=0; i<nbAssoc-1; i++)
    {
        if(associations[i]->tag==tag)
        {
            res[nb]=associations[i]->note;
            nb++;
        }
    }
    return res;
}

QSet<Tag*> TagManager::getTagforNote(Note *note)
{
    QSet<Tag*> res;
    for(unsigned int i=0; i<nbAssoc-1; i++)
    {
        if(associations[i]->note==note)
        {
            res<<associations[i]->tag;
        }
    }
}

void TagManager::removeTagToNote(Tag *tag, Note *note)
{
    for(unsigned int i=0; i<nbAssoc-1; i++) // supprime les associations
    {
        if(associations[i]->tag==tag)
        {
            delete associations[i];
            for(unsigned int j=i; j<nbAssoc-1; j++) associations[j]=associations[j+1];
            nbAssoc--;
        }
    }
}
