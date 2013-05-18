#include "htmlViewer.h"

HtmlViewer::HtmlViewer(Note *n, QWidget *parent) :
    QWidget(parent), ressource(n)
{
    layout = new QVBoxLayout;
    wv = new QWebView();
    wv->setHtml(ressource->toHTML());

    layout->addWidget(wv);

    this->setLayout(layout);
}
