#ifndef VIDEONOTEEDITOR_H
#define VIDEONOTEEDITOR_H
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "BinaryEditor.h"
#include "player/player.h"
class VideoNote;

class VideoNoteEditor : public BinaryEditor
{
    Q_OBJECT
public:
    explicit VideoNoteEditor(VideoNote *v, QWidget* parent = 0);

signals:
public slots:
    void BACKEND_SET_CONTENT();
    void LOAD_VIDEO();
    void CLOSING();
private:
    QPushButton *btnAddVideo;
    Player *videoWidget;
    VideoNote *ressource;
};

#endif // VIDEONOTEEDITOR_H
