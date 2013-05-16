#include "Notes.h"
#include <fstream>
#include <QFile>
#include <QDebug>

Article::Article(const QString& f, const QString& ti, const QString& te):
    filename(f),title(ti),text(te),
    modified(false) // non modifie
{}

void Article::setTitle(const QString& t) {
    modified=true; title=t;
}

void Article::setText(const QString& t) {
    modified=true; text=t;
}

Article::Article(const Article& a):
    title(a.title),filename(a.filename),text(a.text){}

Article& Article::operator=(const Article& a){
    title=a.title; text=a.text; filename=a.filename;
    return *this;
}

Document::Document(const QString& f, const QString& t):
    filename(f),title(t),
    modified(false), // non modifi�
    articles(0),nbArticles(0),nbMaxArticles(0) // initialement, aucun article
{}

Document& Document::operator<<(Article& a){
    if (nbArticles==nbMaxArticles){
        // il faut agrandir le tableau
        Article** newArticles= new Article*[nbMaxArticles+5];
        for(unsigned int i=0; i<nbArticles; i++) newArticles[i]=articles[i];
        Article** oldArticles=articles;
        articles=newArticles;
        nbMaxArticles+=5;
        if (oldArticles) delete[] oldArticles;
    }
    articles[nbArticles++]=&a;
    modified=true;
    return *this;
}

void Document::removeArticle(unsigned int i){
    if (i<nbArticles){
        for(unsigned int j=i; j<nbArticles-1; j++) articles[j]=articles[j+1];
        modified=true;
    }else throw NotesException("error, removing an article");
}

void Document::moveArticleUp(unsigned int i){
    if (i<nbArticles && i>0){
        Article* a=articles[i];
        articles[i]=articles[i-1];
        articles[i-1]=a;
        modified=true;
    }else throw NotesException("error, moving up an article");
}

void Document::moveArticleDown(unsigned int i){
    if (i>=0 && i<nbArticles-1){
        Article* a=articles[i];
        articles[i]=articles[i+1];
        articles[i+1]=a;
        modified=true;
    }else throw NotesException("error, moving down an article");
}

Article& Document::getArticle(unsigned int i){
    if (i>=0 && i<nbArticles){
        return *articles[i];
    }else throw NotesException("error, this article does not exists");
}

const Article& Document::getArticle(unsigned int i) const {
    if (i>=0 && i<nbArticles){
        return *articles[i];
    }else throw NotesException("error, this article does not exists");
}

Document::Document(const Document& m):
    articles(new Article*[m.nbArticles]),
    nbArticles(m.nbArticles),
    nbMaxArticles(m.nbArticles),
    filename(m.filename),title(m.title){
        for(unsigned int i=0; i<nbArticles; i++)
            articles[i]=m.articles[i];
}

Document& Document::operator=(const Document& m){
    if (this!=&m){
        filename=m.filename;
        title=m.title;
        Article** newarticles=new Article*[m.nbArticles];
        for(unsigned int i=0; i<nbArticles; i++)
            newarticles[i]=m.articles[i];
        Article** old=articles;
        articles=newarticles;
        delete[] old;
    }
    return *this;
}

void NotesManager::addArticle(Article* a){
    if (nbArticles==nbMaxArticles){
        Article** newArticles= new Article*[nbMaxArticles+5];
        for(unsigned int i=0; i<nbArticles; i++) newArticles[i]=articles[i];
        Article** oldArticles=articles;
        articles=newArticles;
        nbMaxArticles+=5;
        if (oldArticles) delete[] oldArticles;
    }
    articles[nbArticles++]=a;
}

void NotesManager::addDocument(Document* d){
    if (nbDocuments==nbMaxDocuments){
        Document** newDocuments= new Document*[nbMaxDocuments+5];
        for(unsigned int i=0; i<nbDocuments; i++) newDocuments[i]=documents[i];
        Document** oldDocuments=documents;
        documents=newDocuments;
        nbMaxDocuments+=5;
        if (oldDocuments) delete[] oldDocuments;
    }
    documents[nbDocuments++]=d;
}

Article& NotesManager::getArticle(const QString& fileName){
    // s'il existe d�j�, on le  renvoie
    for(unsigned int i=0; i<nbArticles; i++){
        if (articles[i]->getFilename()==fileName) return *articles[i];
    }
    // sinon, il faut le loader
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString title=flux.readLine();
    QString text=flux.readAll();
    fichier.close();
    Article* a=new Article(fileName,title,text);
    addArticle(a);
    return *a;
}

Document& NotesManager::getDocument(const QString& fileName){
    // on v�rifie d'abord que le document demand� n'a pas d�j� �t� charg�
    for(unsigned int i=0; i<nbDocuments; i++){
        if (documents[i]->getFilename()==fileName) return *documents[i];
    }
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    QString title=flux.readLine();
    Document* d=new Document(fileName,title);
    QString ligne;
    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        (*d)<<(getArticle(ligne));

    }
    addDocument(d);
    return *d;
}

Document& NotesManager::getNewDocument(const QString& filename){
    Document* d=new Document(filename,"");
    d->modified=true;
    addDocument(d);
    return *d;
}

Article& NotesManager::getNewArticle(const QString& filename){
    Article* a=new Article(filename,"","");
    a->modified=true;
    addArticle(a);
    return *a;
}




NotesManager* NotesManager::instance=0; // pointeur sur l'unique instance
NotesManager& NotesManager::getInstance(){
    if (!instance) instance=new NotesManager;
    return *instance;
}
void NotesManager::libererInstance(){
    if (instance) delete instance;
    instance=0;
}


NotesManager::NotesManager():
    documents(0),articles(0),nbDocuments(0),nbArticles(0),nbMaxDocuments(0),nbMaxArticles(0)
    {}


NotesManager::~NotesManager(){
    for(unsigned int i=0; i<nbDocuments; i++){
        saveDocument(*documents[i]);
        delete documents[i];
    }
    for(unsigned int i=0; i<nbArticles; i++) {
        saveArticle(*articles[i]);
        delete articles[i];
    }
    delete[] documents;
    delete[] articles;
}

void NotesManager::saveArticle(Article& a){
    if (a.isModified()) {
        // Cr�ation d'un objet QFile
        QFile file(a.getFilename());
        // On ouvre notre fichier en lecture seule et on v�rifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'un article : impossible d'ouvrir un fichier en �criture");
        QTextStream flux(&file);
        flux<<a;
        file.close();
        a.modified=false;
    }
}

void NotesManager::saveDocument(Document& d){
    if (d.isModified()) {
        // Cr�ation d'un objet QFile
        QFile file(d.getFilename());
        // On ouvre notre fichier en lecture seule et on v�rifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'un document : impossible d'ouvrir un fichier en �criture");
        QTextStream flux(&file);
        flux<<d;
        file.close();
        d.modified=false;
    }
}

QTextStream& operator<<(QTextStream& f, const Article& a){
    f<<a.getTitle()<<"\n";
    f<<a.getText()<<"\n";
    return f;
}

QTextStream& operator<<(QTextStream& f, const Document& d){
    f<<d.getTitle()<<"\n";
    for(unsigned int i=0; i<d.getNbArticles(); i++){
        f<<d.getArticle(i).getFilename()<<"\n";
    }
    return f;
}
