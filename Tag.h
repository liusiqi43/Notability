#ifndef TAG_H
#define TAG_H

#include <QObject>
#include <QString>
#include <QSet>

class Note;

/*!
 * \brief The Tag class un Tag est compose d'un nom et un Ensemble des notes associe.
 * Les tags sont identifie par son noms, il est donc interdit d'avoir deux tags du meme nom.
 */
class Tag
{
    QString name;
    /*!
     * \brief assocs Un ensemblse des notes qui sont associes a ce tag
     */
    QSet<Note*> assocs;

public:
    Tag(const Tag& other);
    Tag(const QString& n);

    QSet<Note*>& getAssocs() { return assocs; }
    /*!
     * \brief addNote associe la Note n a ce tag
     * \param n
     */
    void addNote(Note *n);
    /*!
     * \brief removeNote disassocie la Note n a ce Tag;
     * \param n
     */
    void removeNote(Note* n);
    /*!
     * \brief reset enlever toutes les notes associes
     */
    void reset() {assocs.clear();}
    QString getName() const;
    void setName(const QString &value);

};

#endif // TAG_H
