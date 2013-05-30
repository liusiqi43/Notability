#include "ImageNote.h"
#include "ExportStrategy.h"

/***
 * ImageNote
 */
ImageNote::ImageNote(const QString& filepath)
    :Binary(filepath)
{}

ImageNote::ImageNote(const QString& filePath, const QString& ti, const QString& des, const QString& iPath)
    :Binary(filePath, ti, des, iPath)
{}

ImageNoteEditor *ImageNote::createEditor()
{
    return new ImageNoteEditor(this);
}

QString ImageNote::exportNote(const ExportStrategy *es, unsigned int level)
{
    if(level){
        return es->exportNote(this, level);
    }
    else{
        return es->header()+es->exportNote(this)+es->footer();
    }
}

