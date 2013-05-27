#include "TextExport.h"
#include "Note.h"
#include "Article.h"
#include "ImageNote.h"
#include "AudioNote.h"
#include "VideoNote.h"
#include "Document.h"

//TextExport

QString TextExport::header() const
{
    return "---------Début--------\n";
}

QString TextExport::footer() const
{
    return "----------Fin---------\n";
}

QString TextExport::exportNote(const Article *note, unsigned int level) const
{
    QString margin = "";
    for(unsigned int i=0; i<level; i++){
        margin += "  ";
    }
    return margin+"Title: "+note->getTitle()+"\n"+margin+"Text: "+note->getText()+"\n";
}

QString TextExport::exportNote(const ImageNote *note, unsigned int level) const
{
    QString margin = "";
    for(unsigned int i=0; i<level; i++){
        margin += "  ";
    }
    return margin+"Title: "+note->getTitle()+"\n"+margin+"ImagePath: "+note->getMediaPath()+"\n"+margin+"Description: "+note->getDescription()+"\n";
}

QString TextExport::exportNote(const Document *doc, unsigned int level) const
{
    QString margin = "";
    QString str;
    for(unsigned int i=0; i<level; i++){
        margin += "  ";
    }

    str+=margin+"Title: "+doc->getTitle()+"\n";

    level++;
    for(QSet<Note *>::const_iterator it = doc->begin(); it!=doc->end(); it++)
    {
        str+=(*it)->exportNote(this, level);
    }
    return str;
}

QString TextExport::exportNote(const VideoNote *note, unsigned int level) const
{
    return "@TODO";
}

QString TextExport::exportNote(const AudioNote *note, unsigned int level) const
{
    return "@TODO";
}


