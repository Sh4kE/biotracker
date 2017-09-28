#ifndef BIOTRACKERPLUGIN_H
#define BIOTRACKERPLUGIN_H

#include "biotrackerplugin_global.h"
#include "opencv2/core/core.hpp"
#include "Interfaces/IBioTrackerContext.h"

#include "Interfaces/IBioTrackerPlugin.h"


#include "QPointer"
#include "memory"
#include "QPoint"

class BIOTRACKERPLUGINSHARED_EXPORT BioTrackerPlugin : public IBioTrackerPlugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "de.fu-berlin.mi.biorobotics.BioTrackerPlugin" FILE "BioTrackerPlugin.json")
	Q_INTERFACES(IBioTrackerPlugin)

  public:
	BioTrackerPlugin();

	// IBioTrackerPlugin interface
	IView* getTrackerParameterWidget();
	IView *getTrackerElementsWidget();
	IModel* getTrackerComponentModel();
	void setDataExporter(IModelDataExporter *exporter);

  public:
	void createPlugin();
	void receiveCurrentFrameFromMainApp(std::shared_ptr<cv::Mat> mat, uint frameNumber);
	void sendCorePermissions();

  private:
	void connectInterfaces();
signals:
	void emitCvMat(std::shared_ptr<cv::Mat> mat, QString name);
	void emitTrackingDone(uint framenumber);
	void emitChangeDisplayImage(QString str);
	void emitCorePermission(std::pair<ENUMS::COREPERMISSIONS, bool> permission);
	void emitRemoveTrajectory(IModelTrackedTrajectory* trajectory);
	void emitAddTrajectory(QPoint pos);
	void emitMoveElement(IModelTrackedTrajectory* trajectory, QPoint pos);
	void emitSwapIds(IModelTrackedTrajectory* trajectory0, IModelTrackedTrajectory* trajectory1);
	void emitCurrentFrameNumber(uint frameNumber);

public slots:
	void receiveRemoveTrajectory(IModelTrackedTrajectory* trajectory);
	void receiveAddTrajectory(QPoint pos);
	void receiveMoveElement(IModelTrackedTrajectory* trajectory, QPoint pos);
	void receiveSwapIds(IModelTrackedTrajectory* trajectory0, IModelTrackedTrajectory* trajectory1);

private slots:
	void receiveCvMatFromController(std::shared_ptr<cv::Mat> mat, QString name);
	void receiveTrackingDone(uint framenumber);
	void receiveChangeDisplayImage(QString str);


private:
	IController *m_TrackerController;
	IController *m_ComponentController;
	IController *m_AreaDescrController;

	IBioTrackerContext *m_PluginContext;

public:
	QList<ENUMS::COREPERMISSIONS> m_CorePermissions;


};

#endif // BIOTRACKERPLUGIN_H