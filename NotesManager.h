#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QSet>
#include "Notes.h"
#include "NoteFactory.h"

typedef QSet<Note *>::iterator nSetIt;

class NotesManager {
private:
    QSet<Note*> Notes;

    void addNote(Note* a);

    static std::map<NoteType, NoteFactory*> factories;
//    static std::map<NoteType, ExportStrategy*> strategies;

    NotesManager();
    ~NotesManager();

    NotesManager(const NotesManager&); // non d�fini mais priv� pour emp�cher la duplication
    NotesManager& operator=(const NotesManager&); // m�me chose
    static NotesManager* instance; // pointeur sur l'unique instance


public:
    static NotesManager& getInstance();
    static void libererInstance();
    Note& getNote(const QString& filename);
    ImageNote& getImageNote(const QString& filename);
    Note& getNewNote(NoteType type);
    ImageNote& getNewImageNote();
    void saveNote(Note& a);
    void saveImageNote(ImageNote& i);

    nSetIt begin(){return Notes.begin();}
    nSetIt end(){return Notes.end();}
};

#endif // NOTESMANAGER_H
