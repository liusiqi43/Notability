#include "AudioNoteFactory.h"
#include <QFile>
#include <QTextStream>

/***
 * AudioNoteFactory
 */

AudioNote* AudioNoteFactory::buildNote(const QString &path)
{
    QFile fichier(path);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString title=flux.readLine();
    QString des =flux.readLine();
    QString apath = flux.readLine();

    fichier.close();

    AudioNote* a=new AudioNote(path,title,des,apath);
    return a;
}


AudioNote* AudioNoteFactory::buildNewNote()
{
    return new AudioNote(generateNewFilePath());
}


AudioNote* AudioNoteFactory::buildNoteCopy(const AudioNote &note)
{
    return new AudioNote(generateNewFilePath(), note.getTitle(), note.getDescription(), note.getMediaPath());
}


QString AudioNoteFactory::getFolder()
{
    return "AUD/";
}


QString AudioNoteFactory::getExtension()
{
    return ".aud";
}
