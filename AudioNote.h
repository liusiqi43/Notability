#ifndef AUDIONOTE_H
#define AUDIONOTE_H


#include "Binary.h"
#include "AudioNoteEditor.h"

/*!
 * \brief The AudioNote class Cette classe herite de la Class Binary, qui represente une note qui contient de la musique
 */
class AudioNote: public Binary{
public:
    AudioNote(const QString& filePath);
    AudioNote(const QString& filePath, const QString& ti, const QString& des, const QString& aPath);

    /*!
     * \brief createEditor Creation d'un audioNoteEditor pour lui meme
     * \return un audioNoteEditor qui est rempli avec le contenu de cette note courant
     */
    AudioNoteEditor *createEditor(){return new AudioNoteEditor(this);}
    QString exportNote(const ExportStrategy *es, unsigned int level = 0);
};

#endif // AUDIONOTE_H
