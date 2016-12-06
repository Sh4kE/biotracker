#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "Interfaces/IModel/imodel.h"
#include "QPluginLoader"
#include "QStringListModel"
#include "Interfaces/IBioTrackerPlugin.h"
#include "QPointer"

class PluginLoader : public IModel
{
    Q_OBJECT
public:
    explicit PluginLoader(QObject *parent = 0);

    bool loadPluginFromFilename(QString filename);
    IBioTrackerPlugin *getPluginInstance();

private:

    QPluginLoader *m_PluginLoader;

    QStringList m_PluginList;
    QStringListModel m_PluginListModel;
};

#endif // PLUGINLOADER_H