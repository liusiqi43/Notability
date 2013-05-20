#include "htmlViewer.h"

HtmlViewer::HtmlViewer(const QString& html, QWidget *parent) :
    QWidget(parent), ressource(html)
{
    layout = new QVBoxLayout;
    wv = new QWebView();
    wv->setHtml(ressource);

    layout->addWidget(wv);

    this->setLayout(layout);
}
