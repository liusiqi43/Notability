
#include "NotesManager.h"
#include "Note.h"
#include "NoteFactory.h"
#include "ExportStrategy.h"
#include "NotesException.h"
#include <QString>
#include <QSettings>
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

void NotesManager::addNote(Note* a){

    rootDocument->addNote(a);

    if(a->isDocument())
        DocumentsContainer << static_cast<Document*>(a);
}

void NotesManager::removeNote(Note *a)
{
    rootDocument->removeNote(a);
    if(a->isDocument())
        DocumentsContainer.remove(static_cast<Document*>(a));
}

Note& NotesManager::getNote(const QString& fileName){
    Note* res = rootDocument->find(fileName);
    if(res){
        qDebug()<<"gotcha";
        return *res;
    }

    // sinon, il faut le loader
    NoteType type = DetectType(fileName);
    
    if(type == unknownType)
        throw NotesException("File type not supported now! Please send an email to me@siqi.fr for support! :P");
    
    NoteFactory* f = NotesManager::factories->value(type);
    Note* n = f->buildNote(fileName);
    addNote(n);
    qDebug()<<"New NOTE:::::::::::::::::"<<n->getFilePath();
    n->setModified(false);
    return *n;
}

Note &NotesManager::getNoteClone(const Note& note)
{   
//    if(!mapper)
        // OldPath, NewPath mapper
//        mapper = new QMultiMap<QString, QString>();

    if(mapper->value(note.getFilePath()).isNull()){
        NoteFactory* f = NotesManager::factories->value(note.type);
        Note * n = f->buildNoteCopy(note);
        addNote(n);
        mapper->insert(note.getFilePath(), n->getFilePath());
        return *n;
    } else {
        return *rootDocument->find(mapper->value(note.getFilePath()));
    }
}

Note& NotesManager::getNewNote(NoteType type){
    if(type == unknownType)
        throw NotesException("File type not supported now! Please send an email to me@siqi.fr for support! :P");
    
    NoteFactory* f = NotesManager::factories->value(type);
    Note* n = f->buildNewNote();
    addNote(n);
    return *n;
}


/**
 * @brief NotesManager::instance SINGLETON!
 */
NotesManager* NotesManager::instance=0; // pointeur sur l'unique instance
NotesManager& NotesManager::getInstance(){
    if (!instance)
    {
        instance=new NotesManager;

        // TODO, populates this by file stored on disk.
        QSettings settings;
        QVariant rootPath = settings.value("rootDocument");
        qDebug()<<"rootPath = " << rootPath << "During NotesManager construction";
        if(!rootPath.isNull()){
            Document* old = instance->getRootDocument();
            instance->setRootDocument(static_cast<Document *>(instance->factories->value(document)->buildNote(rootPath.toString())));
            if(!instance->getRootDocument()){
                qDebug()<<"Init loading failed: "<<rootPath;
                instance->setRootDocument(old);
            } else {
                delete old;
            }
            instance->getRootDocument()->setModified(false);
        }
        settings.setValue("workspaceChanged", false);
    }
    return *instance;
}
void NotesManager::libererInstance(){
    if (instance) delete instance;
    instance=0;
}


NotesManager::NotesManager()
    :mapper(0)
{
    mapper = new QMultiMap<QString, QString>();
    factories = NoteFactory::getFactories();
    strategies = ExportStrategy::getStrategies();
    rootDocument = static_cast<Document *>(factories->value(document)->buildNewNote());
    rootDocument->setTitle("~");
}


NotesManager::~NotesManager(){
//    for(nListIt it = begin(); it!= end(); it++) {
//        saveNote((**it));
//        delete *it;
//    }
    delete mapper;
}

void NotesManager::saveDocument(Document& d){

    for(nListIt it = d.begin(); it!= d.end(); ++it){
        if(*it != &d)
            saveNote(**it);
    }

    // Saving in reverse order. So that all path saved are valid

    // Prepare parent directories
    QString fp = d.getFilePath();
    fp.truncate(fp.lastIndexOf('/'));
    QDir().mkpath(fp);

    // Creation d'un objet QFile
    QFile file(d.getFilePath());

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException("Failed to save your note, please check if I have the permission to write on your harddisk and stop hacking the software!");

    ExportStrategy* es = NotesManager::strategies->value(saveText);
    QString q = d.exportNote(es, 0);

    QTextStream flux(&file);
    flux<<q;
    file.close();
    d.setModified(false);
}

void NotesManager::saveNote(Note& a){
    if (a.isModified()) {
        qDebug()<<"saving Note:"<<a.getTitle();
        if(!a.isDocument()){
            // Prepare parent directories
            QString fp = a.getFilePath();
            fp.truncate(fp.lastIndexOf('/'));
            QDir().mkpath(fp);

            // Creation d'un objet QFile
            QFile file(a.getFilePath());

            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                throw NotesException("Failed to save your note, please check if I have the permission to write on your harddisk and stop hacking the software!");

            ExportStrategy* es = NotesManager::strategies->value(saveText);
            QString q = a.exportNote(es);

            QTextStream flux(&file);
            flux<<q;
            file.close();
            a.setModified(false);
        }
        else{
            saveDocument(static_cast<Document&>(a));
        }
    }
    a.setModified(false);
}


Document *NotesManager::getRootDocument() const
{
    return rootDocument;
}

void NotesManager::setRootDocument(Document *value)
{
    rootDocument = value;
}
