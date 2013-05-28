#include "TextViewer.h"
#include <QVBoxLayout>
#include <QTextEdit>

TextViewer::TextViewer(const QString& text, QWidget *parent) :
    QWidget(parent), ressource(text)
{
    layout = new QVBoxLayout;
    tv = new QTextEdit();
    tv->setText(ressource);

    layout->addWidget(tv);

    this->setLayout(layout);
}


