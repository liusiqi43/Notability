#ifndef ARTICLEFACTORY_H
#define ARTICLEFACTORY_H

#include "NoteFactory.h"
#include "Article.h"

class ArticleFactory : public NoteFactory
{
public:
    Article* buildNewNote();
    Article* buildNote(const QString &path);
//    Article* buildNoteCopy(const Article &note);
    QString getFolder();
    QString getExtension();
};

#endif // ARTICLEFACTORY_H
