#include "NotesManager.h"
#include "Notes.h"
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>

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
        if (articles[i]->getFilePath()==fileName) return *articles[i];
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

ImageNote &NotesManager::getImageNote(const QString &fileName)
{
    // s'il existe d�j�, on le  renvoie
//    for(unsigned int i=0; i<nbArticles; i++){
//        if (articles[i]->getFilePath()==fileName) return *articles[i];
//    }
    // sinon, il faut le loader
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString title=flux.readLine();
    QString iPath=flux.readLine();
    QString description=flux.readAll();
    fichier.close();
    ImageNote* a=new ImageNote(title, description, iPath);
//    addArticle(a);
    return *a;
}

Document& NotesManager::getDocument(const QString& fileName){
    // on v�rifie d'abord que le document demand� n'a pas d�j� �t� charg�
    for(unsigned int i=0; i<nbDocuments; i++){
        if (documents[i]->getFilePath()==fileName) return *documents[i];
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
    d->setModified(true);
    addDocument(d);
    return *d;
}

Article& NotesManager::getNewArticle(){
    Article* a=new Article("","");
    a->setModified(true);
    addArticle(a);
    return *a;
}

ImageNote &NotesManager::getNewImageNote()
{
    ImageNote* a=new ImageNote("", "", "");
    a->setModified(true);
    // TODO replace addArticle with addNote
//    addArticle(a);
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
        // Prepare parent directories
        QString fp = a.getFilePath();
        fp.truncate(fp.lastIndexOf('/'));
        QDir().mkpath(fp);

        // Cr�ation d'un objet QFile
        QFile file(a.getFilePath());

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
        QFile file(d.getFilePath());
        // On ouvre notre fichier en lecture seule et on v�rifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'un document : impossible d'ouvrir un fichier en �criture");
        QTextStream flux(&file);
        flux<<d;
        file.close();
        d.modified=false;
    }
}

void NotesManager::saveImageNote(ImageNote &i)
{
    if (i.isModified()) {
        // Prepare parent directories
        QString fp = i.getFilePath();
        fp.truncate(fp.lastIndexOf('/'));
        QDir().mkpath(fp);

        // Cr�ation d'un objet QFile
        QFile file(i.getFilePath());

        // On ouvre notre fichier en lecture seule et on v�rifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'un article : impossible d'ouvrir un fichier en �criture");
        QTextStream flux(&file);
        flux<<i;
        file.close();
        i.modified=false;
    }
}
