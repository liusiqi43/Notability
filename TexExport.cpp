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
    return "\%\%\%\%\%\% These exported files need to use movie15 packages for multimedia support\%\%\%\%\%\n\\documentclass[a4paper,11pt]{report}\n\\usepackage{graphicx}\n\\usepackage{movie15}\n\\usepackage{multimedia}\n\\usepackage[french]{babel}\n\\usepackage[latin1]{inputenc}\n\\usepackage[T1]{fontenc}\n\\begin{document}";
}

QString TexExport::footer() const
{
    return "\n\\end{document}";
}

QString TexExport::exportNote(const Article *note, unsigned int level) const
{
    switch(level){
    case 0:
        return " \n\\chapter{"+note->getTitle()+"}\n"+note->getText();
    case 1:
        return " \n\\section{"+note->getTitle()+"}\n"+note->getText();
    case 2:
        return " \n\\subsection{"+note->getTitle()+"}\n"+note->getText();
    case 3:
        return " \n\\subsubsection{"+note->getTitle()+"}\n"+note->getText();
    case 4:
        return " \n\\paragraph{"+note->getTitle()+"}\n"+note->getText();
    case 5:
        return " \n\\subparagraph{"+note->getTitle()+"}\n"+note->getText();
    default:
        return " \n\\subparagraph{"+note->getTitle()+"}\n"+note->getText();
    }
}

QString TexExport::exportNote(const ImageNote *note, unsigned int level) const
{
    switch(level){
    case 0:
        return " \n\\chapter{"+note->getTitle()+"}\n\\begin{center}\n\\includegraphics{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 1:
        return " \n\\section{"+note->getTitle()+"}\n\\begin{center}\n\\includegraphics{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 2:
        return " \n\\subsection{"+note->getTitle()+"}\n\\begin{center}\n\\includegraphics{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 3:
        return " \n\\subsubsection{"+note->getTitle()+"}\n\\begin{center}\n\\includegraphics{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 4:
        return " \n\\paragraph{"+note->getTitle()+"}\n\\begin{center}\n\\includegraphics{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 5:
        return " \n\\subparagraph{"+note->getTitle()+"}\n\\begin{center}\n\\includegraphics{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    default:
        return " \n\\subparagraph{"+note->getTitle()+"}\n\\begin{center}\n\\includegraphics{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    }
}

QString TexExport::exportNote(const Document *doc, unsigned int level) const
{
    QString str;

    switch(level){
    case 0:
        str+=" \n\\chapter{"+doc->getTitle()+"}";
        break;
    case 1:
        str+=" \n\\section{"+doc->getTitle()+"}";
        break;
    case 2:
        str+=" \n\\subsection{"+doc->getTitle()+"}";
        break;
    case 3:
        str+=" \n\\subsubsection{"+doc->getTitle()+"}";
        break;
    case 4:
        str+=" \n\\paragraph{"+doc->getTitle()+"}";
        break;
    case 5:
        str+=" \n\\subparagraph{"+doc->getTitle()+"}";
        break;
    default:
        str+=" \n\\subparagraph{"+doc->getTitle()+"}";
    }

    level++;
    for(QList<Note *>::const_iterator it = doc->begin(); it!=doc->end(); it++)
    {
        str+=(*it)->exportNote(this, level);
    }
    return str;
}

QString TexExport::exportNote(const VideoNote *note, unsigned int level) const
{
    switch(level){
    case 0:
        return " \n\\chapter{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{320}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 1:
        return " \n\\section{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{320}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 2:
        return " \n\\subsection{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{320}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 3:
        return " \n\\subsubsection{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{320}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 4:
        return " \n\\paragraph{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{320}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 5:
        return " \n\\subparagraph{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{320}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    default:
        return " \n\\subparagraph{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{320}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    }
}

QString TexExport::exportNote(const AudioNote *note, unsigned int level) const
{
    switch(level){
    case 0:
        return " \n\\chapter{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{100}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 1:
        return " \n\\section{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{100}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 2:
        return " \n\\subsection{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{100}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 3:
        return " \n\\subsubsection{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{100}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 4:
        return " \n\\paragraph{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{100}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    case 5:
        return " \n\\subparagraph{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{100}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    default:
        return " \n\\subparagraph{"+note->getTitle()+"}\n\\begin{center}\n\\includemovie[options]{480}{100}{\""+note->getMediaPath()+"\"}\n\\caption{"+note->getDescription()+\
                +"} \n\\end{center}";
    }
}
