#ifndef NOTE_H
#define NOTE_H

#include <QSet>
#include <QString>

#include "Editor.h"
#include "NotesException.h"


class Document;
class ExportStrategy;
class Document;
class Tag;

class Note{
    QString title;
    QString filePath;
    QSet<Tag*> tags;

    // the Editor associated
    Editor* editor;

    // All documents that directly contains this note. For fast access in editors
    QSet<Document*> inDocuments;
    bool modified;
    bool deleted;
    bool document;

public:
    Note(const QString &path);
    Note(const QString &path, const QString& ti);

    virtual ~Note();

    QSet<Tag*>& getTags(){
        return tags;
    }
    void addTag(Tag *tag) {tags << tag;}
    void removeTag(Tag *tag) {tags.remove(tag);}

    // Purement pour facilier a hirarchiser les Notes dans nm.Et puis ca sert a visualiser cette hirarchie dans QTreeView.
    virtual void addNote(Note *){throw NotesException("Should not happen! addNote called for non Document object.");}

    bool operator==(const Note& other);

    const QString &getTitle() const;
    void setTitle(const QString &t);

    const QString &getFilePath() const;
    void setFilePath(const QString &p);

    void setModified(bool b);
    bool isModified() const;

    void setDeleted(bool b);
    bool isDeleted() const;

    Editor *createAndAttachEditor();
    virtual Editor *createEditor() = 0;
    virtual QString exportNote(const ExportStrategy *es, unsigned int level = 0) = 0;

    bool isDocument() const;
    void setDocument(bool value);

    Editor *getEditor() const;
    void setEditor(Editor *value);

    void addToDocument(Document* doc);
    void removeFromDocument(Document *doc);
    bool belongs(Document *doc);
    QSet<Document *>::const_iterator beginInDoc(){return inDocuments.begin();}
    QSet<Document *>::const_iterator endInDoc(){return inDocuments.end();}
    QSet<Document *> getInDocuments() const;
    void setInDocuments(const QSet<Document *> &value);
};



#endif

