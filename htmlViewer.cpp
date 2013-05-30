#include "htmlViewer.h"
#include "viewer.h"
#include <QTextEdit>
#include <QWebView>

HtmlViewer::HtmlViewer(const QString& html, QWidget *parent) :
    Viewer(parent)
{
    layout = new QVBoxLayout;
    wv = new QTextEdit();
    wv->setHtml(html);

    layout->addWidget(wv);

    this->setLayout(layout);
}

void HtmlViewer::setContent(const QString &html)
{
    wv->setHtml(html);
}
