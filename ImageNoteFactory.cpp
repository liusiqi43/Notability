#include "ImageNoteFactory.h"
#include <QFile>
#include <QTextStream>
#include "Article.h"

/***
 * ImageNoteFactory
 */

ImageNote* ImageNoteFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString title=flux.readLine();
    QString des =flux.readLine();
    QString ipath = flux.readLine();

    fichier.close();

    ImageNote* a=new ImageNote(path,title,des,ipath);
    return a;
}


ImageNote* ImageNoteFactory::buildNewNote()
{
    return new ImageNote(generateNewFilePath());
}


ImageNote* ImageNoteFactory::buildNoteCopy(const ImageNote &note)
{
    return new ImageNote(generateNewFilePath(), note.getTitle(), note.getDescription(), note.getMediaPath());
}


QString ImageNoteFactory::getFolder()
{
    return "IMG/";
}


QString ImageNoteFactory::getExtension()
{
    return ".img";
}


