#ifndef BINARY_H
#define BINARY_H

#include "Note.h"

class ExportStrategy;

/**
 * @brief The Binary class. Base class for Image, Audio, VideoNote
 */
class Binary: public Note{
    QString description;
    QString mediaPath;
public:
    Binary(const QString& path);
    Binary(const QString& filePath, const QString& ti, const QString& des, const QString& mediaPath);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getMediaPath() const;
    void setMediaPath(const QString &value);
};


#endif // BINARY_H
