#include "TexViewer.h"

TexViewer::TexViewer(const QString& tex, QWidget *parent)
    :QWidget(parent), ressource(tex)
{
    layout = new QVBoxLayout;
    wv = new QTextEdit();
    wv->setText(ressource);

    layout->addWidget(wv);

    this->setLayout(layout);
}
