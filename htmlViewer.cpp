#include "htmlViewer.h"
#include "viewer.h"
#include <QTextEdit>
#include <QWebView>
#include <QDebug>

HtmlViewer::HtmlViewer(const QString& html, QString mediaPath, QWidget *parent) :
    Viewer(parent)
{
    layout = new QVBoxLayout;
    wv = new QWebView();

    if(!mediaPath.isNull()){
        int pos = mediaPath.lastIndexOf("/");
        mediaPath.truncate(pos+1);
        wv->setHtml(html, mediaPath);
        qDebug()<<"mediaBasePath: "<<mediaPath;
    } else {
        wv->setHtml(html);
    }

    layout->addWidget(wv);

    this->setLayout(layout);
}

void HtmlViewer::setContent(const QString &html, QString mediaPath)
{
    qDebug() << html;
    if(!mediaPath.isNull()){
        int pos = mediaPath.lastIndexOf("/");
        mediaPath.truncate(pos+1);
        wv->setHtml(html, mediaPath);
        qDebug()<<"mediaBasePath: "<<mediaPath;
    } else {
        wv->setHtml(html);
    }
}
