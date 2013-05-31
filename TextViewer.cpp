#include "TextViewer.h"
#include <QVBoxLayout>
#include <QTextEdit>

TextViewer::TextViewer(const QString& text, QWidget *parent) :
    Viewer(parent)
{
    layout = new QVBoxLayout;
    tv = new QTextEdit();
    tv->setText(text);

    layout->addWidget(tv);

    this->setLayout(layout);
}

void TextViewer::setContent(const QString &text)
{
    this->tv->setText(text);
}


