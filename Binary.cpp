#include "Binary.h"
#include "ExportStrategy.h"

/***
 * Binary
 */

Binary::Binary(const QString& path)
    :Note(path), description(""), mediaPath("")
{}
Binary::Binary(const QString& path, const QString& ti, const QString& des, const QString& media)
    :Note(path, ti), description(des), mediaPath(media)
{}

QString Binary::getDescription() const
{
    return description;
}

void Binary::setDescription(const QString &value)
{
    this->setModified(true);
    description = value;
}

QString Binary::getMediaPath() const
{
    return mediaPath;
}

void Binary::setMediaPath(const QString &value)
{
    this->setModified(true);
    mediaPath = value;
}
