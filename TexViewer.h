#ifndef TEXVIEWER_H
#define TEXVIEWER_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class TexViewer : public QWidget
{
    Q_OBJECT
public:
    explicit TexViewer(const QString &, QWidget *parent = 0);
signals:

public slots:
private:
    QVBoxLayout *layout;
    QTextEdit *wv;
    const QString &ressource;
};

#endif // TEXVIEWER_H
