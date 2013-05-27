#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QSet>
#include <QMap>
#include "NoteFactory.h"
#include "ExportStrategy.h"

class Note;
class ImageNote;

typedef QSet<Note *>::iterator nSetIt;

class NotesManager {
private:
    QSet<Note*> Notes;

    void addNote(Note* a);


    NotesManager();
    ~NotesManager();

    NotesManager(const NotesManager&); // non d�fini mais priv� pour emp�cher la duplication
    NotesManager& operator=(const NotesManager&); // m�me chose
    static NotesManager* instance; // pointeur sur l'unique instance


public:
    QMap<ExportType, ExportStrategy*>* strategies;
    QMap<NoteType, NoteFactory*>* factories;
    static NotesManager& getInstance();
    static void libererInstance();
    Note& getNote(const QString& filename);
    Note& getNoteClone(const QString& filename);
    Note& getNewNote(NoteType type);
    void saveNote(Note& a);

    nSetIt begin(){return Notes.begin();}
    nSetIt end(){return Notes.end();}
};

#endif // NOTESMANAGER_H
