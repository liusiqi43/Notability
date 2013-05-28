#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class TextViewer: public QWidget
{
    Q_OBJECT
public:
    explicit TextViewer(const QString &, QWidget *parent = 0);

signals:

public slots:
private:
    QVBoxLayout *layout;
    QTextEdit *tv;
    const QString &ressource;
};

#endif // TEXTVIEWER_H
