#ifndef AUDIONOTEEDITOR_H
#define AUDIONOTEEDITOR_H

#include "BinaryEditor.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QProgressBar>

class AudioNote;

/*!
 * \brief The AudioNoteEditor class Herite de BinaryEditor, qui fournir une UI permettant de choisir les fichiers musique et les controls de musiques
 */
class AudioNoteEditor : public BinaryEditor
{
    Q_OBJECT
public:
    explicit AudioNoteEditor(AudioNote *a, QWidget *parent = 0);
    ~AudioNoteEditor();

signals:

public slots:
    /*!
     * \brief BACKEND_SET_CONTENT Methode qui sauvegarde les donnes specifique au AudioNoteEditor dans l'objet courant
     */
    void BACKEND_SET_CONTENT();
    void LOAD_AUDIO();
    void PLAY_PAUSE_SONG();
    void STOP_SONG();
    /*!
     * \brief SET_VALUE Pour represente l'avancement de la musique
     * \param val l'avancement recupere depuis \link<player>
     */
    void SET_VALUE(qint64 val);

    /*!
     * \brief CLOSING Methode virtuelle de BinaryEditor qui permet d'arreter la musique losqu'on quitte cette editor.
     */
    void CLOSING();

private:
    QPushButton *btnAddAudio;
    QMediaPlayer *player;
    /*!
     * \brief \todo {playlist La possibilite d'ajouter plusieurs musique dans la liste}
     */
    QMediaPlaylist *playlist;
    AudioNote *ressource;
    QPushButton *btnPlayPause;
    QPushButton *btnStop;
    QProgressBar *progression;
    QHBoxLayout *btnLine;
    bool play;

};

#endif // AUDIONOTEEDITOR_H
