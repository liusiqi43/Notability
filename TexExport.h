#ifndef TEXEXPORT_H
#define TEXEXPORT_H

#include "ExportStrategy.h"

/*!
 * \brief The TexExport class Exporter une Note en format TeX.
 */
class TexExport: public ExportStrategy
{
public:
    TexExport(){}
    QString header() const;
    QString footer() const;
    QString exportNote(const ImageNote *note, unsigned int level = 0) const;
    QString exportNote(const Article *note, unsigned int level = 0) const;
    QString exportNote(const AudioNote *note, unsigned int level = 0) const;
    QString exportNote(const VideoNote *note, unsigned int level = 0) const;
    QString exportNote(const Document *doc, unsigned int level = 0) const;
};

#endif // TEXEXPORT_H
