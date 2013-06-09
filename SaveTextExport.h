#ifndef SAVETEXTEXPORT_H
#define SAVETEXTEXPORT_H

#include "ExportStrategy.h"

/*!
 * \brief The SaveTextExport class Exporter les Notes dans un format adapte pour enreigistrer les notes.
 */
class SaveTextExport: public ExportStrategy
{
public:
    SaveTextExport():ExportStrategy(){}
    QString header() const;
    QString footer() const;
    QString exportNote(const ImageNote *note, unsigned int level = 0) const;
    QString exportNote(const Article *note, unsigned int level = 0) const;
    QString exportNote(const AudioNote *note, unsigned int level = 0) const;
    QString exportNote(const VideoNote *note, unsigned int level = 0) const;
    QString exportNote(const Document *doc, unsigned int level = 0) const;
};

#endif // SAVETEXTEXPORT_H
