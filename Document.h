#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Notes.h"
#include <QTextStream>
#include <QString>

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
    const QString& getFilePath() const { return filename; }
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
    void setModified(bool b) {modified = b;}


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

#endif // DOCUMENT_H
