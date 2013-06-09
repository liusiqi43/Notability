#ifndef VIDEONOTEEDITOR_H
#define VIDEONOTEEDITOR_H
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "BinaryEditor.h"
#include <QPushButton>

class Player;
class VideoNote;

/*!
 * \brief The VideoNoteEditor class Editor specialise pour afficher et controler les video
 */
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
    /*!
     * \brief videoWidget Cette classe Player est implemente par la communaute de Qt a titre exemple.
     * L'utilisation de QVideoWidget n'est pourtant pas au point et comporte beaucoup de bugs.
     * Librairie Phonon n'etant pas disponible sur Qt5, on est donc oblige de utilise cette librairie.
     * Ceci fonctionne avec la majorite des formats sous mac, mais pas sous windows. Meme si cela fonctionne sous mac,
     * Il comporte certains erreurs du librairie qui peut eventuellemtn casser le fonctionnement des autres buttons.
     */
    Player *videoWidget;
    VideoNote *ressource;
};

#endif // VIDEONOTEEDITOR_H
