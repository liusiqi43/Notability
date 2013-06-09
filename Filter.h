#ifndef FILTER_H
#define FILTER_H

#include "TreeItem.h"
#include <QSet>
#include <Qmultimap>
#include <QDebug>
#include "Tag.h"

/*!
 * \brief The FilterType enum On compte a present deux types de filtres qui seront utilise pour filter le sideBar.
 */
enum FilterType{tag, search};

/*!
 * \brief The Filter class Type de base pour tous les filtres. Un Filtre doit repondre oui ou non a la question "Est-ce que je doit filtrer le Note* \link<item>?"
 */
class Filter
{
public:
    Filter(){}
    virtual ~Filter(){}
    /*!
     * \brief shallBeFiltered Est-ce que je doit filtrer le Note* \link<item>?. Virtuelle pure. Definition est propre a chaque Filtre
     * \param item
     * \return True si ce \link<item> doit etre filtre, False sinon.
     */
    virtual bool shallBeFiltered(Note *item) const = 0;
};

/*!
 * \brief The TagFilter class Un Filtre qui est base sur les tags.
 */
class TagFilter : public Filter
{
    /*!
     * \brief disabledTags Un ensembles des tags qui devront etre filtres
     */
    QSet<Tag *> disabledTags;

    /*!
     * \brief TagFilter Ce Filtre est un singleton car tout au long du programme on instancie un et un seul Filtre de tags. Au cours du programme on mettre a jour \link <disabledTags> seulement.
     */
    TagFilter():Filter(){}
    TagFilter(const TagFilter&);
    TagFilter& operator=(TagFilter&);

    static TagFilter *instance;
public:
    static TagFilter* getInstance() {if(!instance) instance = new TagFilter(); return instance;}
    static void releaseInstance() {if(instance) delete instance; instance = 0; }

    /*!
     * \brief contains Adaptation du QSet
     * \param tag
     * \return
     */
    bool contains(Tag *tag) {return disabledTags.contains(tag);}
    void addDisabledTag(Tag* tag) {
//        qDebug()<<"adding disabled tag: " << tag->getName();
        disabledTags << tag;
    }
    void removeDisabledTag(Tag* tag) {disabledTags.remove(tag);}

    /*!
     * \brief shallBeFiltered \link<item> est-t-il associe a un des disabledTags?
     * \param item
     * \return True si oui, False sinon.
     */
    bool shallBeFiltered(Note *item) const;
};


class SearchFilter : public Filter
{
    /*!
     * \brief enabledTitleContaining Tous les notes qui contients cet QString doit etre conserves. Les autres seront filtres
     */
    QString enabledTitleContaining;
    SearchFilter():Filter(){}
    SearchFilter(const SearchFilter&);
    SearchFilter& operator=(SearchFilter&);

    static SearchFilter* instance;
public:
    static SearchFilter* getInstance() {if(!instance) instance = new SearchFilter(); return instance;}
    static void releaseInstance() {if(instance) delete instance; instance = 0;}
    void setEnabledTitleContaining(const QString& str) {enabledTitleContaining = str;}
    /*!
     * \brief shallBeFiltered Retourner True si \link<item> ne contient pas \link<enabledTitleContaining>
     * \param item
     * \return
     */
    bool shallBeFiltered(Note *item) const;
};

/*!
 * \brief The FilterKit class Cette classe rassemble un ensemble des Filtres. En utilisant l'interface de \link<Filter>, on peut determine si un item peut survivre apres tous les filtres.
 */
class FilterKit {
    QMultiMap<FilterType, Filter *> filters;
    FilterKit(){}
    ~FilterKit(){
        for(QMultiMap<FilterType, Filter*>::iterator it = filters.begin(); it!=filters.end(); ++it){
            delete (*it);
        }
    }
    static FilterKit* instance;

    FilterKit& operator=(const FilterKit& k);
    FilterKit(const FilterKit&);
public:
    /*!
     * \brief getInstance Cette kit est un singleton
     * \return
     */
    static FilterKit* getInstance();

    void releaseInstance(){
        if(instance)
            delete instance;
        instance = 0;
    }
    /*!
     * \brief setFilter On utilise un multiMap pour gerer les Filtres.
     * \param type Type associe et sert comme cle du filtre
     * \param f
     */
    void setFilter(FilterType type, Filter*f){filters.replace(type, f);}
    Filter* getFilter(FilterType type){return *(filters.find(type));}
    /*!
     * \brief isFilteredByFilters Methode template pour determine si une Note sera fitlre ou pas par un des filtres.
     * \return True si on le filtre, False sinon.
     */
    bool isFilteredByFilters(Note *) const;
    void clear(){filters.clear();}
};


#endif // FILTER_H
