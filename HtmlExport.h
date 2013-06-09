#ifndef HTMLEXPORT_H
#define HTMLEXPORT_H

#include "ExportStrategy.h"

/*!
 * \brief The HtmlExport class Exporter les differentes types de notes en html.
 */
class HtmlExport: public ExportStrategy
{
public:
    HtmlExport(){}
    QString header() const;
    QString footer() const;
    QString exportNote(const ImageNote *note, unsigned int level = 0) const;
    QString exportNote(const Article *note, unsigned int level = 0) const;
    QString exportNote(const AudioNote *note, unsigned int level = 0) const;
    QString exportNote(const VideoNote *note, unsigned int level = 0) const;
    QString exportNote(const Document *doc, unsigned int level = 0) const;
};

#endif // HTMLEXPORT_H
