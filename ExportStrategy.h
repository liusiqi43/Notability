#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include <QString>
#include <QMap>
#include "Tag.h"

class ImageNote;
class Article;
class Document;
class AudioNote;
class VideoNote;
class TagManager;

enum ExportType {html=1, text, saveText, tex, unkownType};

class ExportStrategy
{
protected:
    /*!
     * \brief tm TagManager est utilise dans tous les SaveTextExport car on doit sauvegarder les tags associes.
     */
    TagManager * tm;
public:
    static QMap<ExportType, ExportStrategy*>* getStrategies();

    ExportStrategy();

    QString TagsToString(const QSet<Tag *> &set) const;

    virtual QString exportNote(const ImageNote *note, unsigned int level = 0) const = 0;
    virtual QString exportNote(const Article *note, unsigned int level = 0) const = 0;
    virtual QString exportNote(const AudioNote *note, unsigned int level = 0) const = 0;
    virtual QString exportNote(const VideoNote *note, unsigned int level = 0) const = 0;
    virtual QString exportNote(const Document *doc, unsigned int level = 0) const = 0;

    virtual QString header() const=0;
    virtual QString footer() const=0;
};

#endif // EXPORTSTRATEGY_H
