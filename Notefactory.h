#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <QString>
#include <iostream>
#include <QMap>

class Article;
class ImageNote;
class AudioNote;
class VideoNote;
class Document;
class TagManager;
class Note;

enum NoteType {article=1, document, imageNote, videoNote, audioNote, unknownType};

/*!
 * \brief The NoteFactory class La classe de base pour tous les Factory.
 */
class NoteFactory
{
protected:
    TagManager *tm;
public:
    QString generateID();
    static QMap<NoteType, NoteFactory*>* getFactories();

    NoteFactory();

    /*!
     * \brief buildArticleCopy Method qui construire une copie de \link<note>. Utilise lors du changement de l'espace de travail.
     * Cette methode renvoie une copie de \link<note> du meme type et le meme contenue sauf que la copie generee possede une nouvelle chemin.
     * \param note
     * \return
     */
    Article * buildArticleCopy(const Article& note);
    /*!
     * \brief buildDocumentCopy Method qui construire une copie de \link<note>. Utilise lors du changement de l'espace de travail.
     * Cette methode renvoie une copie de \link<note> du meme type et le meme contenue sauf que la copie generee possede une nouvelle chemin.
     * \param note
     * \return
     */
    Document * buildDocumentCopy(const Document &note);
    /*!
     * \brief buildImageNoteCopy Method qui construire une copie de \link<note>. Utilise lors du changement de l'espace de travail.
     * Cette methode renvoie une copie de \link<note> du meme type et le meme contenue sauf que la copie generee possede une nouvelle chemin.
     * \param note
     * \return
     */
    ImageNote * buildImageNoteCopy(const ImageNote& note);
    /*!
     * \brief buildAudioNoteCopy Method qui construire une copie de \link<note>. Utilise lors du changement de l'espace de travail.
     * Cette methode renvoie une copie de \link<note> du meme type et le meme contenue sauf que la copie generee possede une nouvelle chemin.
     * \param note
     * \return
     */
    AudioNote * buildAudioNoteCopy(const AudioNote& note);
    /*!
     * \brief buildVideoNoteCopy Method qui construire une copie de \link<note>. Utilise lors du changement de l'espace de travail.
     * Cette methode renvoie une copie de \link<note> du meme type et le meme contenue sauf que la copie generee possede une nouvelle chemin.
     * \param note
     * \return
     */
    VideoNote * buildVideoNoteCopy(const VideoNote& note);

    /*!
     * \brief generateNewFilePath
     * \return ceci est une methode template qui concatene le retour de getFoler(), une id unique genera a l'aide d'horologe systeme et une extension genere dans les classes filles.
     * Utilisation de horloge seul a precision d'un ms ne suffit pas pour le programme car los du changement de l'espace de travail, le temps que l'ordintateur copies les notes risque de prendre moins qu'un ms.
     * On utilise ici une incrementation de note a note pour assurer unicite de identifiant des notes.
     */
    virtual QString generateNewFilePath();
    virtual Note* buildNote(const QString& path) = 0;
    virtual Note* buildNewNote() = 0;
    Note* buildNoteCopy(const Note& n);
    /*!
     * \brief getFullFolder
     * \return Retourne l'espace de travail. S'il est pas precise par utilisateur, l'espace de travail est la repertoire courant du programme.
     */
    QString getFullFolder();

    /*!
     * \brief getFolder cf \link<generateNewFilePath()>
     * \return
     */
    virtual QString getFolder() = 0;

    /*!
     * \brief getExtension cf \link<generateNewFilePath()>
     * \return
     */
    virtual QString getExtension() = 0;

};

#endif // NOTEFACTORY_H
