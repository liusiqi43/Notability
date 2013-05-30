#include "VideoNoteFactory.h"
#include <QFile>
#include <QTextStream>

/***
 * VideoNoteFactory
 */

VideoNote* VideoNoteFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;
    QTextStream flux(&fichier);

    QString fpath = flux.readLine();
    QString title=flux.readLine();
    QString des =flux.readLine();
    QString vpath = flux.readLine();

    fichier.close(); qDebug()<<fpath;

    VideoNote* a=new VideoNote(fpath,title,des,vpath);
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
