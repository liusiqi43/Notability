#ifndef TEXVIEWER_H
#define TEXVIEWER_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include "viewer.h"

/*!
 * \brief The TexViewer class Afficheur pour une representation TeX d'une note.
 */
class TexViewer : public Viewer
{
    Q_OBJECT
public:
    explicit TexViewer(const QString &, QWidget *parent = 0);
    void setContent(const QString& tex);
signals:

public slots:
private:
    QVBoxLayout *layout;
    QTextEdit *wv;
};

#endif // TEXVIEWER_H
