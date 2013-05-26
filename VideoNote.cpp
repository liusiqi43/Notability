#include "VideoNote.h"
#include "ExportStrategy.h"

/***
 * VideoNote
 */
VideoNote::VideoNote(const QString& path)
    :Binary(path)
{}
VideoNote::VideoNote(const QString& filePath, const QString& ti, const QString& des, const QString& vPath)
    :Binary(filePath, ti, des, vPath)
{}

//VideoNoteEditor* VideoNote::createEditor(){
//    return new VideoNoteEditor(this);
//}

QString VideoNote::exportNote(const ExportStrategy *es, unsigned int level)
{
    if(level){
        return es->exportNote(this, level);
    }
    else{
        return es->header()+es->exportNote(this)+es->footer();
    }
}

