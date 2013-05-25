#include "NotesManager.h"
#include "Notes.h"
#include "NoteFactory.h"
#include <QString>
#include <QMap>
#include <QFile>
#include <QDir>
#include <QTextStream>

NoteType DetectType(const QString& fileName){
    if(fileName.endsWith(".art")){
        return article;
    }
    else if(fileName.endsWith(".doc")){
        return document;
    }
    else if(fileName.endsWith(".img")){
        return imageNote;
    }
    else if(fileName.endsWith(".aud")){
        return audioNote;
    }
    else if(fileName.endsWith(".vid")){
        return videoNote;
    }
    else
        return unknownType;
}

QMap<NoteType, NoteFactory*> factories = NoteFactory::getFactories();
//std::map<NoteType, NoteFactory*> strategies = ExportStrategy::getStrategies();

void NotesManager::addNote(Note* a){
    // QSet will deduplicate automatically, as we have an ID attribute in Note.
    // If Note does not have an ID attribute, we can only use QSet<Note> as it will compares its address and hash.
    Notes << a;
}

Note& NotesManager::getNote(const QString& fileName){
    for(nSetIt it = begin(); it != end(); it++){
        if((**it).getFilePath()==fileName)
            return (**it);
    }
    // sinon, il faut le loader
    NoteType type = DetectType(fileName);

    if(type == unknownType)
        throw NotesException("File type not supported now! Please send an email to me@siqi.fr for support! :P");

    NoteFactory* f = NotesManager::factories[type];
    Note* n = f->buildNote(fileName);
    addNote(n);
    return *n;
}

Note& NotesManager::getNewNote(NoteType type){
    if(type == unknownType)
        throw NotesException("File type not supported now! Please send an email to me@siqi.fr for support! :P");

    NoteFactory* f = NotesManager::factories[type];
    Note* n = f->buildNewNote();
    addNote(n);
    return *n;
}


/**
 * @brief NotesManager::instance SINGLETON!
 */
NotesManager* NotesManager::instance=0; // pointeur sur l'unique instance
NotesManager& NotesManager::getInstance(){
    if (!instance) instance=new NotesManager;
    return *instance;
}
void NotesManager::libererInstance(){
    if (instance) delete instance;
    instance=0;
}


NotesManager::NotesManager(){}


NotesManager::~NotesManager(){
    for(nSetIt it = begin(); it!= end(); it++) {
        saveNote((**it));
        delete *it;
    }
}

void NotesManager::saveNote(Note& a){
    if (a.isModified()) {
        // Prepare parent directories
        QString fp = a.getFilePath();
        fp.truncate(fp.lastIndexOf('/'));
        QDir().mkpath(fp);

        // Creation d'un objet QFile
        QFile file(a.getFilePath());

        // On ouvre notre fichier en lecture seule et on v�rifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Failed to save your note, please check if I have the permission to write on your harddisk and stop hacking the software!");

        // TODO add enum ExportType {html=1, text, saveText, tex};
        ExportStrategy* es = NotesManager::strategies[saveText];
        QString q = a.exportNote(es, 0);

        QTextStream flux(&file);
        flux<<q;
        file.close();
        a.modified=false;
    }
    else{
        throw NotesException("You are not supposed to save! No modification made!");
    }
}