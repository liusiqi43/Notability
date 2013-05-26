#ifndef NOTESEXCEPTION_H
#define NOTESEXCEPTION_H

#include <QString>

class NotesException{
public:
    NotesException(const QString& message);
    QString getInfo() const;
private:
    QString info;
};


#endif // NOTESEXCEPTION_H
