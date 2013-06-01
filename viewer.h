#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include "NotesException.h"

class Viewer : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);
    virtual void setContent(const QString&){
        throw NotesException("Should not happen, base class implementation called");
    }
signals:
    
public slots:
    
};

#endif // VIEWER_H
