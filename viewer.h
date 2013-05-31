#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>

class Viewer : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);
    virtual void setContent(const QString&) = 0;
signals:
    
public slots:
    
};

#endif // VIEWER_H
