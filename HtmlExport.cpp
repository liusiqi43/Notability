#include "HtmlExport.h"
#include "Note.h"
#include "ImageNote.h"
#include "Article.h"
#include "VideoNote.h"
#include "AudioNote.h"
#include "Document.h"
#include "ExportStrategy.h"

//Html Export
QString HtmlExport::header() const
{
    return "<html><head><meta charset=\"UTF-8\"><title></title></head><body>";
}

QString HtmlExport::footer() const
{
    return "</body></html>";
}

QString HtmlExport::exportNote(const ImageNote *note, unsigned int level) const
{
    QString str;
    // Shoud implement a limit on margin...TODO
    int margin = level * 10;
    int titleSize = 6 ? level > 6 : level;

    str+= "<div style=\"margin-left:"+QString(margin)+"+px;>";
    str+="<h"+QString(titleSize)+">"+note->getTitle()+ \
            "</h"+QString(titleSize)+"><img style=\"width: 100%\" src=file://\""+note->getMediaPath()+"\" alt=\"\"><p>"\
            +note->getDescription()+"</p></div>";
    return str;
}

QString HtmlExport::exportNote(const Article *note, unsigned int level) const
{
    QString str;
    // Shoud implement a limit on margin...TODO
    int margin = level * 10;
    int titleSize = 6 ? level > 6 : level;

    str+= "<div style=\"margin-left:"+QString(margin)+"+px;>";
    str+="<h"+QString(titleSize)+">"+note->getTitle()+ \
            "</h"+QString(titleSize)+"><p>"+note->getText()+"</p></div>";
    return str;
}

QString HtmlExport::exportNote(const AudioNote *note, unsigned int level) const
{
    QString str;
    // Shoud implement a limit on margin...TODO
    int margin = level * 10;
    int titleSize = 6 ? level > 6 : level;

    str+= "<div style=\"margin-left:"+QString(margin)+"+px;>";
    str+="<h"+QString(titleSize)+">"+note->getTitle()+ \
            "</h"+QString(titleSize)+"><p>"+"@TODO"+note->getDescription()+"</p></div>";
    return str;
}

QString HtmlExport::exportNote(const VideoNote *note, unsigned int level) const
{
    QString str;
    // Shoud implement a limit on margin...TODO
    int margin = level * 10;
    int titleSize = 6 ? level > 6 : level;

    str+= "<div style=\"margin-left:"+QString(margin)+"+px;>";
    str+="<h"+QString(titleSize)+">"+note->getTitle()+ \
            "</h"+QString(titleSize)+"><p>"+"@TODO"+note->getDescription()+"</p></div>";
    return str;
}

QString HtmlExport::exportNote(const Document *doc, unsigned int level) const
{
    QString str;
    str="<h1>"+doc->getTitle()+"</h1>";
    ++level;
    for(QSet<Note *>::const_iterator it = doc->begin(); it!=doc->end(); it++)
    {
        str+=(*it)->exportNote(this, level);
    }
    return str;
}
