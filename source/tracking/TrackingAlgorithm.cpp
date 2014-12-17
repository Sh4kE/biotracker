#include "TrackingAlgorithm.h"

TrackingAlgorithm::TrackingAlgorithm(Settings &settings, QWidget *parent)
	: QObject(parent)
	, _settings(settings)
	, _currentFrameNumber(0)
	, _currentZoomLevel(0.0f)
{}

void TrackingAlgorithm::loadObjects(std::vector<TrackedObject>&& objects)
{
	_trackedObjects = std::move(objects);
	postLoad();
}

const std::vector<TrackedObject> &TrackingAlgorithm::getObjects()
{
	prepareSave();
	return _trackedObjects;
}

std::shared_ptr<QWidget> TrackingAlgorithm::getToolsWidget()
{
	return std::make_shared<QWidget>();
}

std::shared_ptr<QWidget> TrackingAlgorithm::getParamsWidget()
{
	return std::make_shared<QWidget>();
}

const std::set<Qt::Key> &TrackingAlgorithm::grabbedKeys() const
{
	static const std::set<Qt::Key> keys;
	return keys;
}

bool TrackingAlgorithm::event(QEvent *event)
{
	const QEvent::Type etype = event->type();
	switch (etype) {
	case QEvent::KeyPress:
		keyPressEvent(static_cast<QKeyEvent*>(event));
		return true;
		break;
	case QEvent::MouseButtonPress:
		mousePressEvent(static_cast<QMouseEvent*>(event));
		return true;
		break;
	case QEvent::MouseButtonRelease:
		mouseReleaseEvent(static_cast<QMouseEvent*>(event));
		return true;
		break;
	case QEvent::MouseMove:
		mouseMoveEvent(static_cast<QMouseEvent*>(event));
		return true;
		break;
	case QEvent::Wheel:
		mouseWheelEvent(static_cast<QWheelEvent*>(event));
	default:
		event->ignore();
		return false;
	}
}

boost::optional<cv::Mat> TrackingAlgorithm::getCurrentImageCopy() const
{
	if (_currentImage) return _currentImage.get().clone();
	else return boost::optional<cv::Mat>();
}

void TrackingAlgorithm::prepareSave()
{}

void TrackingAlgorithm::postLoad()
{}
