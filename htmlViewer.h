#ifndef HTMLVIEWER_H
#define HTMLVIEWER_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWebView>
#include "viewer.h"

class HtmlViewer : public Viewer
{
    Q_OBJECT
public:
    explicit HtmlViewer(const QString &, QString mediaPath = QString(), QWidget *parent = 0);
    void setContent(const QString& html, QString mediaPath = QString());
signals:
    
public slots:
private:
    QVBoxLayout *layout;
    QWebView *wv;
};

#endif // HTMLVIEWER_H
