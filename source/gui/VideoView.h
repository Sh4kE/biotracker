#pragma once

#include <chrono>

#include <QGLWidget>
#include <QtOpenGL>

#include <opencv2/opencv.hpp>

#include "source/core/settings/Messages.h"
#include "source/core/TrackingAlgorithm.h"
#include "source/util/stdext.h"
#include "source/gui/TextureObject.h"

namespace BioTracker {
namespace Gui {

class VideoView : public QGLWidget
{
	Q_OBJECT
public:
    VideoView(QWidget *parent = nullptr);
    ~VideoView();
	void showImage(cv::Mat img);
	void updateDisplay();
	void takeScreenshot(QString screenShotFilename);
	float getCurrentZoomLevel() const { return _screenPicRatio + _zoomFactor; }

    friend class ::ProxyPaintObject;

protected:
	void initializeGL() override;
	void paintEvent(QPaintEvent *) override;
	void resizeGL(int width, int height) override;
    // unproject Point from window coordinates to picture coordinates
    QPoint unprojectScreenPos(QPoint mouseCoords);
    // project Point from picture coordinates to window coordinates
    QPoint projectPicturePos(QPoint pictureCoords);
	void keyPressEvent(QKeyEvent *e) override;
	void mouseMoveEvent(QMouseEvent * e) override;
	void mousePressEvent(QMouseEvent * e) override;
	void mouseReleaseEvent(QMouseEvent * e) override;
	void wheelEvent(QWheelEvent * e) override;

private:
	cv::Mat _displayImage;
    std::unique_ptr<TextureObject> _textureObj;
	std::shared_ptr<TrackingAlgorithm> _tracker;    
	bool _isPanZoomMode;
	int _currentWidth;
	int _currentHeight;

	/**
	* Modified by user input. 
	* Initially 0, geting negative if we zoom into the picture,
	* getting positive if we zoom out
	*/
	float _zoomFactor;
	/* ratio of window size to picture size */
	float _screenPicRatio;
	float _panX;
	float _panY;
	bool _isPanning;
	int _lastMPos[2];
	std::chrono::system_clock::time_point _lastPannedTime;
	std::chrono::system_clock::time_point _lastZoomedTime;
	QPoint _lastZoomedPoint;
	TrackingAlgorithm::View _selectedView;

public slots:
	void setTrackingAlgorithm(std::shared_ptr<TrackingAlgorithm> trackingAlgorithm);
	void setPanZoomMode (bool isPanZoom);
	void fitToWindow();

	void changeSelectedView(const TrackingAlgorithm::View &selectedView);

signals:
	/**
	* print a message in GUI's terminal.
	*/
	void notifyGUI(std::string message, MSGS::MTYPE type = MSGS::MTYPE::NOTIFICATION);

	/**
	* notify TrackingAlgorithm about current zoom level
	*/
	void reportZoomLevel(float);
};

}
}
