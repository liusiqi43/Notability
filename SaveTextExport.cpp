#include "SaveTextExport.h"
#include "Note.h"
#include "Article.h"
#include "ImageNote.h"
#include "AudioNote.h"
#include "VideoNote.h"
#include "Document.h"
#include "TagManager.h"

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
    QString str;
    str += note->getFilePath()+"\n"+note->getTitle()+"\n";
    str += TagsToString(note->getTags()) + "\n";
    str += note->isDeleted() ? "isDeleted\n" : "notDeleted\n";
    str += note->getText()+"\n";
    return str;
}

QString SaveTextExport::exportNote(const ImageNote *note, unsigned int level) const
{
    QString str;

    str += note->getFilePath()+"\n"+note->getTitle()+"\n";
    str += TagsToString(note->getTags()) + "\n";
    str += note->isDeleted() ? "isDeleted\n" : "notDeleted\n";
    str += note->getDescription()+"\n";
    str += note->getMediaPath()+"\n";

    return str;
}

QString SaveTextExport::exportNote(const Document *doc, unsigned int level) const
{
    QString str;
    str+=doc->getFilePath()+"\n";
    str+=doc->getTitle()+"\n";
    str+= TagsToString(doc->getTags()) + "\n";
    str+= doc->isDeleted() ? "isDeleted\n" : "notDeleted\n";

    for(QList<Note *>::const_iterator it = doc->begin(); it!=doc->end(); it++)
    {
        str+=(*it)->getFilePath()+"\n";
    }
    return str;
}

QString SaveTextExport::exportNote(const AudioNote *note, unsigned int level) const
{
    QString str;

    str += note->getFilePath()+"\n"+note->getTitle()+"\n";
    str += TagsToString(note->getTags()) + "\n";
    str += note->isDeleted() ? "isDeleted\n" : "notDeleted\n";
    str += note->getDescription()+"\n";
    str += note->getMediaPath()+"\n";

    return str;
}

QString SaveTextExport::exportNote(const VideoNote *note, unsigned int level) const
{
    QString str;

    str += note->getFilePath()+"\n"+note->getTitle()+"\n";
    str += TagsToString(note->getTags()) + "\n";
    str += note->isDeleted() ? "isDeleted\n" : "notDeleted\n";
    str += note->getDescription()+"\n";
    str += note->getMediaPath()+"\n";

    return str;
}

