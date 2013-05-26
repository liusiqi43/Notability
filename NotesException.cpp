#include "NotesException.h"

/***
 * NotesException
 */
NotesException::NotesException(const QString& message):info(message){}
QString NotesException::getInfo() const { return info; }
