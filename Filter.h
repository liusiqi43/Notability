#ifndef FILTER_H
#define FILTER_H

#include "TreeItem.h"
#include <QSet>
#include <Qmultimap>
#include "Tag.h"

enum FilterType{tag, search};

class Filter
{
public:
    Filter(){}
    virtual ~Filter(){}
    virtual bool shallBeFiltered(Note *item) const = 0;
};

class TagFilter : public Filter
{
    QSet<Tag *> enabledTags;
public:
    TagFilter():Filter(){}
    void addEnabledTag(Tag* tag) {enabledTags << tag;}
    void removeEnabledTag(Tag* tag) {enabledTags.remove(tag);}
    bool shallBeFiltered(Note *item) const;
};

class SearchFilter : public Filter
{
    const QString enabledTitleContaining;
public:
    SearchFilter(const QString & shouldContains):Filter(), enabledTitleContaining(shouldContains){}
    bool shallBeFiltered(Note *item) const;
};


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
    static FilterKit* getInstance();

    void releaseInstance(){
        if(instance)
            delete instance;
        instance = 0;
    }

    void setFilter(FilterType type, Filter*f){filters.replace(type, f);}
    Filter* getFilter(FilterType type){return *(filters.find(type));}
    bool isFilteredByFilters(Note *) const;
    void clear(){filters.clear();}
};


#endif // FILTER_H
