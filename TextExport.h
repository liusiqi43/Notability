#ifndef TEXTEXPORT_H
#define TEXTEXPORT_H

#include "ExportStrategy.h"

class TextExport: public ExportStrategy
{
public:
    TextExport(){}
    QString header() const;
    QString footer() const;
    QString exportNote(const ImageNote *note, unsigned int level = 0) const;
    QString exportNote(const Article *note, unsigned int level = 0) const;
    QString exportNote(const AudioNote *note, unsigned int level = 0) const;
    QString exportNote(const VideoNote *note, unsigned int level = 0) const;
    QString exportNote(const Document *doc, unsigned int level = 0) const;
};

#endif // TEXTEXPORT_H
