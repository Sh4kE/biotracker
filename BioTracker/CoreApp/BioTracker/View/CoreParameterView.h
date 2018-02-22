#ifndef COREPARAMETERVIEW_H
#define COREPARAMETERVIEW_H

#include "Interfaces/IView/IViewWidget.h"
//TODO add default parameters accesible via config
//#include "Model/CoreViewParameter.h"

namespace Ui {
	class CoreParameterView;
}

class CoreParameterView : public IViewWidget
{
	Q_OBJECT

public:
	explicit CoreParameterView(QWidget *parent = 0, IController *controller = 0, IModel *model = 0);
	~CoreParameterView();

	QWidget* getTrackerHook();
	void setPermission(std::pair<ENUMS::COREPERMISSIONS, bool> permission);

    // Triggers re-sending essential signals
    void triggerUpdate();

    void areaDescriptorTypeChanged(QString type);

	private slots:
	//Enable view
	void on_checkBoxEnableCoreView_stateChanged(int v);
	//Tracing
	void on_comboBoxTracingStyle_currentIndexChanged(const QString & text);
	void on_spinBoxTracingHistoryLength_valueChanged(int i);
	void on_spinBoxTracingSteps_valueChanged(int i);
	void on_comboBoxTracingTimeDegradation_currentIndexChanged(const QString & text);
	void on_checkBoxTracerFrameNumber_stateChanged(int toggle);

	void on_spinBoxTracerProportions_valueChanged(double d);
	void on_checkBoxTracerOrientationLine_stateChanged(int toggle);

	//Track 
	//void on_pushButtonSelectAll_clicked();
	//void on_pushButtonAddTrack_clicked();

	void on_checkBoxIgnoreZoom_stateChanged(int v);

	//Track color
	void on_pushButtonColorChangeBorder_clicked();
	void on_pushButtonColorChangeBorderSelected_clicked();
	void on_pushButtonColorChangeBrush_clicked();
	void on_pushButtonColorchangeBrushSelected_clicked();
	
	//Track dimensions
	void on_checkBoxTrackOrientationLine_stateChanged(int v);
	void on_checkBoxShowId_stateChanged(int v);


	void on_pushButtonTrackDimensionSetterAll_clicked();
	void on_pushButtonTrackDimensionSetterSelected_clicked();
	void on_pushButtonDefaultDimensions_clicked();

	//Area descriptor
	void on_lineEditRectWidth_textChanged(QString s);
	void on_lineEditRectHeight_textChanged(QString s);
	void on_checkBoxDisplayTrackingArea_stateChanged(int v);
	void on_checkBoxDisplayRectification_stateChanged(int v);
	void on_checkboxTrackingAreaAsEllipse_stateChanged(int v);

	//Finalize experiment
    void on_pushButtonFinalizeExperiment_clicked();

	//Misc
	void on_checkBoxExpertOptions_stateChanged(int v);
	void on_checkBoxAntialiasingEntities_stateChanged(int v);
	void on_checkBoxAntialiasingFull_stateChanged(int v);

public:
	signals :

			//Enable aiew
            void emitViewSwitch(bool lever);
			//Select all tracks
            //void emitSelectAll();
			//Set number of tracks
			void emitAddTrack();
			//Ignore zoom
			void emitIgnoreZoom(bool toggle);
			//Track color
			void emitColorChangeBorderAll();
			void emitColorChangeBorderSelected();
			void emitColorChangeBrushAll();
			void emitColorChangeBrushSelected();
			//Track dimensions
			void emitTrackOrientationLine(bool toggle);
			void emitTrackShowId(bool toggle);
			void emitTrackDimensionsAll(int width, int height);
			void emitTrackDimensionsSelected(int width, int height);
			void emitTrackDimensionsSetDefault();
			//Tracing
			void emitTracingHistoryLength(int history);
			void emitTracingStyle(QString style);
			void emitTracingSteps(int steps);
			void emitTracingTimeDegradation(QString degradation);
			void emitTracerFrameNumber(bool toggle);
			//Tracing dimensions
			void emitTracerProportions(float proportion);
			void emitTracerOrientationLine(bool toggle);

			//Area descriptor
			void emitRectDimensions(double w, double h);
			void emitDisplayTrackingArea(bool b);
			void emitDisplayRectification(bool b);
            void emitTrackingAreaAsEllipse(bool b);

			//Finalize Experiment
            void emitFinalizeExperiment();

			//Misc
			void emitToggleAntialiasingEntities(bool toggle);
			void emitToggleAntialiasingFull(bool toggle);

private:
	Ui::CoreParameterView *ui;

	bool m_viewSwitch;

	// IViewWidget interface
	public slots:

	void getNotified();
	void fillUI();
	void setStyle();
};

#endif // COREPARAMETERVIEW_H
