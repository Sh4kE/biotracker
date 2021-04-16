#include "DataExporterGeneric.h"
#include "util/types.h"
#include "Utility/misc.h"
#include <qdebug.h>
#include <QFile>
#include <QTextStream>
#include <qdatetime.h>

using namespace BioTrackerUtilsMisc; //split

DataExporterGeneric::DataExporterGeneric(QObject *parent) :
    IModelDataExporter(parent)
{
    _parent = static_cast<ControllerDataExporter*>(parent);
    _cfg = static_cast<IControllerCfg*>(parent)->getConfig();
    _root = 0;
}

void DataExporterGeneric::open(IModelTrackedTrajectory *root) {
    _root = root;
    
    _tmpFile = _parent->generateBasename(true).toStdString() + ".tmp" + getSuffix().toStdString();
    _finalFile = _parent->generateBasename(false).toStdString() + getSuffix().toStdString();

    if(_cfg->UseMediaName){

        ControllerDataExporter *ctr = dynamic_cast<ControllerDataExporter*>(_parent);
        std::string mPath = ctr->getMediaPath();
        if(mPath != ""){
            this->setFinalFileFromMediaName(QString::fromStdString(mPath));
        }
    }

    //_ofs.open(_tmpFile, std::ofstream::out);

    //QFile _oFileTmp(QString::fromStdString(_tmpFile));
    _oFileTmp = new QFile(QString::fromStdString(_tmpFile));
    _oFileTmp->open(QIODevice::WriteOnly);
    
    if(!_oFileTmp->isOpen()){
        qWarning() << "File could not be opened! " << QString::fromStdString(_tmpFile);
    }

    _ofs.setDevice(_oFileTmp);

    if(!_ofs.device()){
        qDebug() << "Failed to assign device to tmp-QTextStream";
    }
}

int DataExporterGeneric::getMaxLinecount()
{
    if (_root == nullptr)
        return 0;

    int max = 0;
    for (int i = 0; i < _root->size(); i++) {
        IModelTrackedTrajectory *t = dynamic_cast<IModelTrackedTrajectory *>(_root->getChild(i));
        if (t) max = std::max(t->size(), max);
    }

    return max;
}

void DataExporterGeneric::cleanup()
{
    int s = _root->size();

    //Erase all tracking data from the tracking structure!
    _root->clear();

    // close tmp file and textstream
    if (_oFileTmp->isOpen()) {
        _oFileTmp->close();
    }
    if (_ofs.device()){
        _ofs.setDevice(0);
    }

    //Remove temporary file
    QFile file(_tmpFile.c_str());
    file.remove();

    if (s > 0) {
        //Tell the controller about the written file
        QFileInfo fi(_finalFile.c_str());
        Q_EMIT fileWritten(fi);
    }
    return;
}

void DataExporterGeneric::setFinalFileFromMediaName(QString path){
    QFileInfo mediaFile(path);
    QString mediaName = mediaFile.baseName();

    QString outDir = _cfg->DirTracks;

    std::string outPath = getTimeAndDate(outDir.toStdString() + mediaName.toStdString() + "_", "");
    _finalFile = outPath + getSuffix().toStdString();
}

void DataExporterGeneric::finalize()
{
    close();
    writeAll("");
    cleanup();
};
