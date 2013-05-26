#ifndef ARTICLE_H
#define ARTICLE_H

#include "ArticleEditor.h"
#include "Note.h"

class ExportStrategy;

class Article: public Note {
    QString text;

public:

    Article(const QString& filePath);
    Article(const QString& path, const QString& ti, const QString& te);

    const QString& getText() const;
    void setText(const QString& t);

    ArticleEditor *createEditor();
    QString exportNote(const ExportStrategy *es, unsigned int level = 0);
};


#endif // ARTICLE_H
