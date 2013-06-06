#include "Filter.h"
#include "Note.h"

TagFilter *TagFilter::instance = 0;

bool SearchFilter::shallBeFiltered(Note *item) const
{
    return !item->getTitle().contains(enabledTitleContaining, Qt::CaseInsensitive);
}


bool FilterKit::isFilteredByFilters(Note *item) const
{
    for(QMap<FilterType, Filter*>::const_iterator it = filters.begin(); it!=filters.end(); ++it){
        if((*it)->shallBeFiltered(item))
            return true;
    }
    return false;
}

FilterKit* FilterKit::instance=0; // pointeur sur l'unique instance
FilterKit* FilterKit::getInstance(){
    if(!instance)
        instance = new FilterKit();
    return instance;
}



bool TagFilter::shallBeFiltered(Note *item) const
{
//    qDebug() << "DisabledTags size: " << disabledTags.size();
    // filtrer les notes
    for(QSet<Tag*>::const_iterator it=disabledTags.begin(); it!=disabledTags.end(); it++)
    {
        if((*it)->getAssocs().contains(item)) return true;
    }
    return false;
}
