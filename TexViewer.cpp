#include "TexViewer.h"

TexViewer::TexViewer(const QString& tex, QWidget *parent)
    :Viewer(parent)
{
    layout = new QVBoxLayout;
    wv = new QTextEdit();
    wv->setText(tex);

    layout->addWidget(wv);

    this->setLayout(layout);
}

void TexViewer::setContent(const QString &tex)
{
    this->wv->setText(tex);
}
