#ifndef IMAGENOTEEDITOR_H
#define IMAGENOTEEDITOR_H

#include "BinaryEditor.h"
//#include "ImageNote.h"

class ImageNote;

class ImageNoteEditor : public BinaryEditor
{
    Q_OBJECT
public:
    explicit ImageNoteEditor(ImageNote *img, MainWindow *mw, QWidget *parent = 0);

signals:

public slots:
    void BACKEND_SET_CONTENT();
    void LOAD_IMAGE();

private:
    QPushButton *btnAddImage;
    QPixmap image;
    QLabel *imageWidget;
    ImageNote *ressource;
    QString currentImgPath;
};

#endif // IMAGENOTEEDITOR_H
