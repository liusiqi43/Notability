#ifndef VIDEONOTEEDITOR_H
#define VIDEONOTEEDITOR_H

#include "BinaryEditor.h"
class VideoNote;

class VideoNoteEditor : public BinaryEditor
{
    Q_OBJECT
public:
    explicit VideoNoteEditor(VideoNote *v, MainWindow *mw, QWidget* parent = 0);

signals:
public slots:
    void BACKEND_SET_CONTENT();
private:

};

#endif // VIDEONOTEEDITOR_H
