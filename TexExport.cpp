#include "TexExport.h"
#include "Note.h"
#include "Article.h"
#include "ImageNote.h"
#include "AudioNote.h"
#include "VideoNote.h"
#include "Document.h"

//TexExport

QString TexExport::header() const
{
    return "\\documentclass[a4paper,11pt]{report} \\usepackage{graphicx}\\usepackage{multimedia} %utilisé pour inclure des images%gestion de la police\\usepackage[french]{babel}\\usepackage[latin1]{inputenc}\\usepackage[T1]{fontenc}\\begin{document}";
}

QString TexExport::footer() const
{
    return "\\end{document}";
}

QString TexExport::exportNote(const Article *note, unsigned int level) const
{
    switch(level){
    case 0:
        return " \\chapter{"+note->getTitle()+"}\\\\"+note->getText();
    case 1:
        return " \\section{"+note->getTitle()+"}\\\\"+note->getText();
    case 2:
        return " \\subsection{"+note->getTitle()+"}\\\\"+note->getText();
    case 3:
        return " \\subsubsection{"+note->getTitle()+"}\\\\"+note->getText();
    case 4:
        return " \\paragraph{"+note->getTitle()+"}\\\\"+note->getText();
    case 5:
        return " \\subparagraph{"+note->getTitle()+"}\\\\"+note->getText();
    default:
        return " \\subparagraph{"+note->getTitle()+"}\\\\"+note->getText();
    }
}

QString TexExport::exportNote(const ImageNote *note, unsigned int level) const
{
    switch(level){
    case 0:
        return " \\chapter{"+note->getTitle()+"}\\\\%Ajout d’image\\begin{center}\\includegraphics{"+note->getMediaPath()+"}\\caption{"+note->getDescription()+\
                +"} \\end{center}";
    case 1:
        return " \\section{"+note->getTitle()+"}\\\\%Ajout d’image\\begin{center}\\includegraphics{"+note->getMediaPath()+"}\\caption{"+note->getDescription()+\
                +"} \\end{center}";
    case 2:
        return " \\subsection{"+note->getTitle()+"}\\\\%Ajout d’image\\begin{center}\\includegraphics{"+note->getMediaPath()+"}\\caption{"+note->getDescription()+\
                +"} \\end{center}";
    case 3:
        return " \\subsubsection{"+note->getTitle()+"}\\\\%Ajout d’image\\begin{center}\\includegraphics{"+note->getMediaPath()+"}\\caption{"+note->getDescription()+\
                +"} \\end{center}";
    case 4:
        return " \\paragraph{"+note->getTitle()+"}\\\\%Ajout d’image\\begin{center}\\includegraphics{"+note->getMediaPath()+"}\\caption{"+note->getDescription()+\
                +"} \\end{center}";
    case 5:
        return " \\subparagraph{"+note->getTitle()+"}\\\\%Ajout d’image\\begin{center}\\includegraphics{"+note->getMediaPath()+"}\\caption{"+note->getDescription()+\
                +"} \\end{center}";
    default:
        return " \\subparagraph{"+note->getTitle()+"}\\\\%Ajout d’image\\begin{center}\\includegraphics{"+note->getMediaPath()+"}\\caption{"+note->getDescription()+\
                +"} \\end{center}";
    }
}

QString TexExport::exportNote(const Document *doc, unsigned int level) const
{
    QString str;

    switch(level){
    case 0:
        str+=" \\chapter{"+doc->getTitle()+"}";
    case 1:
        str+=" \\section{"+doc->getTitle()+"}";
    case 2:
        str+=" \\subsection{"+doc->getTitle()+"}";
    case 3:
        str+=" \\subsubsection{"+doc->getTitle()+"}";
    case 4:
        str+=" \\paragraph{"+doc->getTitle()+"}";
    case 5:
        str+=" \\subparagraph{"+doc->getTitle()+"}";
    default:
        str+=" \\subparagraph{"+doc->getTitle()+"}";
    }

    level++;
    for(QSet<Note *>::const_iterator it = doc->begin(); it!=doc->end(); it++)
    {
        str+=(*it)->exportNote(this, level);
    }
    return str;
}

QString TexExport::exportNote(const VideoNote *note, unsigned int level) const
{
    return "@TODO";
}

QString TexExport::exportNote(const AudioNote *note, unsigned int level) const
{
    return "@TODO";
}
