#ifndef ARTICLE_H
#define ARTICLE_H

#include "ArticleEditor.h"
#include "Note.h"

class ExportStrategy;

/*!
 * \brief The Article class Cette classe hérite de Note, qui contient un attribut text en plus.
 */
class Article: public Note {
    QString text;

public:

    Article(const QString& filePath);
    Article(const QString& path, const QString& ti, const QString& te);

    const QString& getText() const;
    void setText(const QString& t);

    /*!
     * \brief createEditor Méthode virtuelle qui est implémentée dans la classe fille. Cette méthode créer un \link<ArticleEditor> qui hérite à son tour de \link<Editor>
     * \return
     */
    ArticleEditor *createEditor();

    /*!
     * \brief exportNote Cette methode retourne une representation de note selon le type de ExportStrategy.
     * \param es Le type de \link<ExportStrategy>
     * \param level le niveau d'indentation.
     * \return
     */
    QString exportNote(const ExportStrategy *es, unsigned int level = 0);
};


#endif // ARTICLE_H
