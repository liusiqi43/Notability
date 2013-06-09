#include "ExportStrategy.h"
#include "HtmlExport.h"
#include "TexExport.h"
#include "TextExport.h"
#include "SaveTextExport.h"
#include "TagManager.h"
#include "Tag.h"
#include <QMap>

//QMap<ExportType, ExportStrategy*> ExportStrategy::strategies = QMap<ExportType, ExportStrategy*>();

//ExportStrategy
ExportStrategy::ExportStrategy()
{
    tm = &TagManager::getInstance();
}

/*!
 * \brief ExportStrategy::TagsToString Convertir un QSet de tags en String, separer par |||
 * \param set l'ensemble a convertir.
 * \return
 */
QString ExportStrategy::TagsToString(const QSet<Tag*>& set) const{
    QString str;
    for(QSet<Tag*>::const_iterator it = set.begin(); it!=set.end(); ++it){
        str += (*it)->getName() + "|||";
    }
    if(!str.isNull())
        str.chop(3);
    return str;
}

/*!
 * \brief ExportStrategy::getStrategy retourner tous les \link<ExportStrategy> disponibles
 * \return un QMap de <ExportType, ExportStrategy>.
 */
QMap<ExportType, ExportStrategy*>* ExportStrategy::getStrategies()
{
    QMap<ExportType, ExportStrategy*> *strategies = new QMap<ExportType, ExportStrategy*>();
    strategies->insert(html, new HtmlExport());
    strategies->insert(tex, new TexExport());
    strategies->insert(text, new TextExport());
    strategies->insert(saveText, new SaveTextExport());

    return strategies;
}



