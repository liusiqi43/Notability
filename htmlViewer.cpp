#include "htmlViewer.h"
#include "viewer.h"
#include <QTextEdit>
#include <QWebView>
#include <QDebug>

HtmlViewer::HtmlViewer(const QString& html, QWidget *parent) :
    Viewer(parent)
{
    layout = new QVBoxLayout;
    wv = new QWebView();

    wv->setHtml(html);

    layout->addWidget(wv);

    this->setLayout(layout);
}

void HtmlViewer::setContent(const QString &html)
{
    qDebug() << html;

    wv->setHtml(html);

}
