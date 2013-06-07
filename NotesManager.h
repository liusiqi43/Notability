#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QList>
#include <QMap>
#include "Document.h"
#include "NoteFactory.h"
#include "ExportStrategy.h"

class Note;
class ImageNote;

// On préfère QList car il garde l'ordre. Et c'est bizarre si on n'affiche pas les notes dans l'ordre d'ajout
typedef QList<Note *>::const_iterator nListIt;
typedef QSet<Document *>::const_iterator dSetIt;

class NotesManager {
private:
    // Used for fast access to a list of all opened documents
    QSet<Document *> DocumentsContainer;
    QMultiMap<QString, QString> *mapper;
    Document *rootDocument;

    void addNote(Note* a);

    NotesManager();
    ~NotesManager();

    NotesManager(const NotesManager&); // non d�fini mais priv� pour emp�cher la duplication
    NotesManager& operator=(const NotesManager&); // m�me chose
    static NotesManager* instance; // pointeur sur l'unique instance

    void saveDocument(Document& d);

public:
    void removeNote(Note* a);
    QMap<ExportType, ExportStrategy*>* strategies;
    QMap<NoteType, NoteFactory*>* factories;
    static NotesManager& getInstance();
    static void libererInstance();
    Note& getNote(const QString& filename);
    Note& getNoteClone(const Note &note);
    Note& getNewNote(NoteType type);
    void saveNote(Note& a);

    nListIt begin(){return rootDocument->begin();}
    nListIt end(){return rootDocument->end();}

    dSetIt beginDocumentContainer(){return DocumentsContainer.begin();}
    dSetIt endDocumentContainer(){return DocumentsContainer.end();}
    Document *getRootDocument() const;
    void setRootDocument(Document *value);
};

#endif // NOTESMANAGER_H
