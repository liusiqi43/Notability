#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include "viewer.h"

class TextViewer: public Viewer
{
    Q_OBJECT
public:
    explicit TextViewer(const QString &, QWidget *parent = 0);
    void setContent(const QString& text);
signals:

public slots:
private:
    QVBoxLayout *layout;
    QTextEdit *tv;
};

#endif // TEXTVIEWER_H
