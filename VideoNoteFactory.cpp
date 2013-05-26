#include "VideoNoteFactory.h"
#include <QFile>
#include <QTextStream>

/***
 * VideoNoteFactory
 */

VideoNote* VideoNoteFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString title=flux.readLine();
    QString des =flux.readLine();
    QString vpath = flux.readLine();

    fichier.close();

    VideoNote* a=new VideoNote(path,title,des,vpath);
    return a;
}


VideoNote* VideoNoteFactory::buildNewNote()
{
    return new VideoNote(generateNewFilePath());
}


VideoNote* VideoNoteFactory::buildNoteCopy(const VideoNote &note)
{
    return new VideoNote(generateNewFilePath(), note.getTitle(), note.getDescription(), note.getMediaPath());
}


QString VideoNoteFactory::getFolder()
{
    return "VID/";
}


QString VideoNoteFactory::getExtension()
{
    return ".vid";
}
