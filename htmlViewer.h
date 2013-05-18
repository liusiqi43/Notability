#ifndef HTMLVIEWER_H
#define HTMLVIEWER_H

#include <QWidget>
#include <QWebView>
#include <QVBoxLayout>

#include "Notes.h"

class HtmlViewer : public QWidget
{
    Q_OBJECT
public:
    explicit HtmlViewer(Note *n, QWidget *parent = 0);
    
signals:
    
public slots:
private:
    QVBoxLayout *layout;
    QWebView *wv;
    Note *ressource;
};

#endif // HTMLVIEWER_H
