#ifndef HTMLVIEWER_H
#define HTMLVIEWER_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWebView>
#include <QPlainTextEdit>
#include "viewer.h"

/*!
 * \brief The HtmlViewer class Un afficheur pour afficher les HTML dans un webview.
 */
class HtmlViewer : public Viewer
{
    Q_OBJECT
public:
    explicit HtmlViewer(const QString &, QWidget *parent = 0);
    /*!
     * \brief setContent L'interface qui permet d'actualise le contenu du WebView.
     * \param html
     */
    void setContent(const QString& html);
signals:
    
public slots:
    void SWITCH_BETWEEN_TV_AND_WV(bool checked);
private:
    QVBoxLayout *layout;
    QWebView *wv;
    QPlainTextEdit *tv;
};

#endif // HTMLVIEWER_H
