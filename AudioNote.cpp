#include "AudioNote.h"
#include "ExportStrategy.h"

/***
 * AudioNote
 */
AudioNote::AudioNote(const QString& filePath)
    :Binary(filePath)
{}
AudioNote::AudioNote(const QString& filePath, const QString& ti, const QString& des, const QString& aPath)
    :Binary(filePath, ti, des, aPath)
{}

//AudioNoteEditor* AudioNote::createEditor(){
//    return new AudioNoteEditor(this);
//}

QString AudioNote::exportNote(const ExportStrategy *es, unsigned int level)
{
    if(level){
        return es->exportNote(this, level);
    }
    else{
        return es->header()+es->exportNote(this)+es->footer();
    }
}
