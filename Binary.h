#ifndef BINARY_H
#define BINARY_H

#include "Note.h"

class ExportStrategy;

/*!
 * \brief The Binary class Base class pour Image, Audio, VideoNote. Cette classe comporte un attribute mediaPath, qui represente le chemin vers le fichier multimedia.
 */
class Binary: public Note{
    /*!
     * \brief description Description du media.
     */
    QString description;
    QString mediaPath;
public:
    Binary(const QString& path);
    Binary(const QString& filePath, const QString& ti, const QString& des, const QString& mediaPath);

    /*!
     * \brief getDescription Ces attributs communes aux toutes les notes multimedias sont traite a ce niveau la.
     * \return
     */
    QString getDescription() const;
    void setDescription(const QString &value);

    QString getMediaPath() const;
    void setMediaPath(const QString &value);
};


#endif // BINARY_H
