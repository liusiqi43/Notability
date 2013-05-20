#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "Notes.h"
#include "Document.h"

class NotesManager {
private:
    Document** documents;
    Article** articles;
    unsigned int nbDocuments;
    unsigned int nbArticles;
    unsigned int nbMaxDocuments;
    unsigned int nbMaxArticles;
    void addArticle(Article* a);
    void addDocument(Document* d);
    NotesManager();
    ~NotesManager();
    NotesManager(const NotesManager&); // non d�fini mais priv� pour emp�cher la duplication
    NotesManager& operator=(const NotesManager&); // m�me chose
    static NotesManager* instance; // pointeur sur l'unique instance
public:
    static NotesManager& getInstance();
    static void libererInstance();
    Document& getDocument(const QString& filename);
    Article& getArticle(const QString& filename);
    ImageNote& getImageNote(const QString& filename);
    Document& getNewDocument(const QString& filename);
    Article& getNewArticle();
    ImageNote& getNewImageNote();
    void saveArticle(Article& a);
    void saveDocument(Document& d);
    void saveImageNote(ImageNote& i);

    enum typeElement { article, document};
    class Iterator {
        friend class NotesManager;
        Article** currentA;
        Document** currentD;
        unsigned int nbRemain;
        Iterator(Article** a, Document** d, unsigned nb):currentA(a),currentD(d),nbRemain(nb){}
    public:
        Iterator():currentA(0),currentD(0),nbRemain(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone()) throw NotesException("error, next on an iterator which is done");
            nbRemain--;
            if (currentA) currentA++; else currentD++;
        }
        Article& currentArticle() {
            if (currentD) throw NotesException("bad use of currentArticle on Iterator");
            return **currentA;
        }
        Document& currentDocument() {
            if (currentA) throw NotesException("bad use of currentArticle on Iterator");
            return **currentD;
        }

    };
    Iterator getIterator(typeElement e) {
        if (e==article) return Iterator(articles,0,nbArticles);
        else return Iterator(0,documents,nbDocuments);
    }
};

#endif // NOTESMANAGER_H
