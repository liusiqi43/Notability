#ifndef NOTES_H
#define NOTES_H

#include <QString>
#include <QTextStream>

class Article;
class Document;
class NotesManager;


QTextStream& operator<<(QTextStream& f, const Article& a);
QTextStream& operator<<(QTextStream& f, const Document& d);

class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

class Article {
    friend class NotesManager;
    QString filename;
    QString title;
    QString text;
    bool modified;
    Article(const Article&);
    Article& operator=(const Article&);
public:
    Article(const QString& f, const QString& ti, const QString& te);
    const QString& getFilename() const { return filename; }
    const QString& getTitle() const { return title; }
    const QString& getText() const { return text; }
    void setTitle(const QString& t);
    void setText(const QString& t);
    bool isModified() const { return modified; }
};

class Document {
    friend class NotesManager;
    Article** articles;
    unsigned int nbArticles;
    unsigned int nbMaxArticles;
    QString filename;
    QString title;
    bool modified;
    Document(const Document& m);
    Document& operator=(const Document& m);
public:
    Document(const QString& f, const QString& t);
    ~Document() { delete[] articles; }
    const QString& getFilename() const { return filename; }
    const QString& getTitle() const { return title; }
    void setTitle(const QString& t) {modified=true; title=t;}
    unsigned int getNbArticles() const { return nbArticles; }
    Document&  operator<<(Article& a);
    Article& getArticle(unsigned int i);
    const Article& getArticle(unsigned int i) const;
    void removeArticle(unsigned int i);
    void moveArticleUp(unsigned int i);
    void moveArticleDown(unsigned int i);
    bool isModified() const { return modified; }



    class Iterator {
        int nbRemain;
        Article** current;
        friend class Document;
        Iterator(Article** c, int n):nbRemain(n),current(c){}
    public:
        Iterator():nbRemain(0),current(0){}
        bool isDone() const { return nbRemain==0; }
        void next() { if (isDone()) throw NotesException("error, next on an iterator which is done"); nbRemain--; current++; }
        Article& currentItem() const { return **current; }
    };
    Iterator getIterator() { return Iterator(articles,nbArticles); }

    class ConstIterator {
        int nbRemain;
        Article** current;
        friend class Document;
        ConstIterator(Article** c, int n):nbRemain(n),current(c){}
    public:
        ConstIterator():nbRemain(0),current(0){}
        bool isDone() const { return nbRemain==0; }
        void next() { if (isDone()) throw NotesException("error, next on an iterator which is done"); nbRemain--; current++; }
        const Article& currentItem() const { return **current; }
    };
    ConstIterator getIterator() const { return ConstIterator(articles,nbArticles); }
};

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
    Document& getNewDocument(const QString& filename);
    Article& getNewArticle(const QString& filename);
    void saveArticle(Article& a);
    void saveDocument(Document& d);

    enum typeElement { article, document};
    class Iterator {
        friend class NotesManager;
        Article** currentA;
        Document** currentD;
        unsigned int nbRemain;
        Iterator(Article** a, Document** d, unsigned nb):currentA(a),currentD(d),nbRemain(nb){}
    public:
        Iterator():nbRemain(0),currentA(0),currentD(0){}
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

#endif

