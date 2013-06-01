//#ifndef TAGMANAGER_H
//#define TAGMANAGER_H

//#include "Tag.h"
//#include <QObject>
//#include <QSet>

//class Note;

//typedef QSet<Tag* >::iterator nSetIt;

//class TagManager // singleton
//{
//    TagManager();
//    ~TagManager();
//    TagManager(const TagManager& tag);
//    TagManager& operator=(const TagManager& t);

//    static TagManager* instance;

//    QSet<Tag*> Tags;


//public:
//    // Ajouter une methode Tag* getTag(const QString newTag);
//    // qui creer un nouveau tag s'il n'existe pas encore,
//    // et retourner le tag existant s'il existe deja.
//    static TagManager& getInstance(); //
//    static void libereInstance(); //
//    QSet<Tag *> getTags(); //
//    void createTag(const QString &n); //
//    void removeTag(Tag* t); //
//    QSet<Tag *> getTagforNote(Note* note);
//    QSet<Note*> getNoteforTag(Tag *tag); //
//    void addTagToNote(Tag *tag, Note *note); //
//    void removeTagToNote(Tag* tag, Note* note);

//    nSetIt begin(){return Tags.begin();}
//    nSetIt end(){return Tags.end();}
//};

//#endif // TAGMANAGER_H
