#include "SaveTextExport.h"
#include "Note.h"
#include "Article.h"
#include "ImageNote.h"
#include "AudioNote.h"
#include "VideoNote.h"
#include "Document.h"

//SaveTextExport

QString SaveTextExport::header() const
{
    return "";
}

QString SaveTextExport::footer() const
{
    return "";
}

QString SaveTextExport::exportNote(const Article *note, unsigned int level) const
{
    return note->getTitle()+"\n"+note->getText()+"\n";
}

QString SaveTextExport::exportNote(const ImageNote *note, unsigned int level) const
{
    return note->getTitle()+"\n"+note->getDescription()+"\n"+note->getMediaPath()+"\n";
}

QString SaveTextExport::exportNote(const Document *doc, unsigned int level) const
{
    QString str;
    str+=doc->getTitle()+"\n";

    for(QList<Note *>::const_iterator it = doc->begin(); it!=doc->end(); it++)
    {
        str+=(*it)->getFilePath()+"\n";
    }
    return str;
}

QString SaveTextExport::exportNote(const AudioNote *note, unsigned int level) const
{
    return note->getTitle()+"\n"+note->getDescription()+"\n"+note->getMediaPath()+"\n";
}

QString SaveTextExport::exportNote(const VideoNote *note, unsigned int level) const
{
    return note->getTitle()+"\n"+note->getDescription()+"\n"+note->getMediaPath()+"\n";
}

