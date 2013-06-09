#ifndef ARTICLEEDITOR_H
#define ARTICLEEDITOR_H

#include "Editor.h"
#include <QPlainTextEdit>

class Article;
/*!
 * \brief The ArticleEditor class Cette classe herite de la superclass Editor, qui s'occupe de configuration genenrale des editors. Cette classe ne s'occupe que de la specialisation de la classe. (textWidget entre autres)
 */
class ArticleEditor : public Editor
{
    Q_OBJECT
public:
    explicit ArticleEditor(Article *, QWidget *parent = 0);

    QPlainTextEdit *getTextWidget() const;
    void setTextWidget(QPlainTextEdit *value);

signals:

public slots:
    /*!
     * \brief BACKEND_SET_CONTENT Cette methode sauvegarde les donnes dans l'objet associe. Il est a noter que cette methode virtuelle ne s'occupe que de la partie specialise (le titleWidget par ex, est traite dans la superclasse)
     */
    void BACKEND_SET_CONTENT();

private:
    QPlainTextEdit *textWidget;
    Article *ressource;
};

#endif // ARTICLEEDITOR_H
