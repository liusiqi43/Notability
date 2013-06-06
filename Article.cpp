#include "Article.h"
#include "ExportStrategy.h"

/***
 *  Article
 */

Article::Article(const QString& path):
    Note(path),text("") {type = article;}

Article::Article(const QString& path, const QString& ti, const QString& te):
    Note(path, ti),text(te) {type = article;}

const QString& Article::getText() const { return text; }

void Article::setText(const QString& t) {
    setModified(true);
    text=t;
}

ArticleEditor *Article::createEditor()
{
    return new ArticleEditor(this);
}

QString Article::exportNote(const ExportStrategy *es, unsigned int level)
{
    if(level){
        return es->exportNote(this, level);
    }
    else{
        return es->header()+es->exportNote(this)+es->footer();
    }
}
