#include "htmlViewer.h"
#include "viewer.h"
#include <QTextEdit>
#include <QWebView>
#include <QDebug>
#include <QCheckBox>

HtmlViewer::HtmlViewer(const QString& html, QWidget *parent) :
    Viewer(parent)
{
    layout = new QVBoxLayout;
    wv = new QWebView();
    tv = new QPlainTextEdit();
    QCheckBox *checkbox = new QCheckBox("Source Code?");
    tv->setHidden(true);
    tv->setPlainText(html);
    wv->setHtml(html);
    layout->addWidget(checkbox);
    layout->addWidget(tv);
    layout->addWidget(wv);

    QObject::connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(SWITCH_BETWEEN_TV_AND_WV(bool)));
    this->setLayout(layout);
}

void HtmlViewer::setContent(const QString &html)
{
    qDebug() << html;

    wv->setHtml(html);

}

void HtmlViewer::SWITCH_BETWEEN_TV_AND_WV(bool checked){
    if(checked){
        wv->setHidden(true);
        tv->setHidden(false);
    } else {
        tv->setHidden(true);
        wv->setHtml(tv->toPlainText());
        wv->setHidden(false);
    }
}
