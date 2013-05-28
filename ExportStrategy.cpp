#include "ExportStrategy.h"
#include "HtmlExport.h"
#include "TexExport.h"
#include "TextExport.h"
#include "SaveTextExport.h"
#include <QMap>

//QMap<ExportType, ExportStrategy*> ExportStrategy::strategies = QMap<ExportType, ExportStrategy*>();

//ExportStrategy
ExportStrategy::ExportStrategy()
{}

QMap<ExportType, ExportStrategy*>* ExportStrategy::getStrategies()
{
    QMap<ExportType, ExportStrategy*> *strategies = new QMap<ExportType, ExportStrategy*>();
    strategies->insert(html, new HtmlExport());
    strategies->insert(tex, new TexExport());
    strategies->insert(text, new TextExport());
    strategies->insert(saveText, new SaveTextExport());

    return strategies;
}



