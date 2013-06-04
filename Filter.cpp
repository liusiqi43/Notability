#include "Filter.h"
#include "Note.h"

bool SearchFilter::shallBeFiltered(Note *item) const
{
//    qDebug()<<"Keep all notes that contain : "+enabledTitleContaining;
//    qDebug()<<"Testing note: " << item->getTitle();
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
    // filtrer les notes
    return false;
}
