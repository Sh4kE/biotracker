#ifndef TrackingAlgorithm_H
#define TrackingAlgorithm_H

#include <vector>
#include <memory>
#include <set>

#include <boost/optional.hpp>

#include <opencv2/opencv.hpp>

#include <QWidget>
#include <QMouseEvent>

#include "settings/Messages.h"
#include "settings/ParamNames.h"
#include "serialization/TrackedObject.h"

namespace BioTracker {
namespace Gui {
class VideoView;
}
}

class ProxyPaintObject {
  private:
    cv::Mat m_img;
    ProxyPaintObject(const ProxyPaintObject &) = delete;
    ProxyPaintObject &operator=(const ProxyPaintObject &) = delete;

  public:
    ProxyPaintObject(cv::Mat img):
        m_img(img) {
    }
    cv::Mat &getmat() {
        return m_img;
    }


};

class Settings;
namespace Algorithm {
typedef uint8_t Type;
}

class TrackingAlgorithm : public QObject {
    Q_OBJECT

  public:
    TrackingAlgorithm(Settings &settings, QWidget *parent);
    virtual ~TrackingAlgorithm() override = default;

    struct View {
        std::string name;
    };

    static const View OriginalView;

    /**
    * This function tracks the provided object list within the provided frame.
    */
    virtual void track(ulong frameNumber, const cv::Mat &frame) = 0;

    /**
    * paint will be called by "VideoViews" paintEvent method
    * so any picture manipulation stuff goes in here
    */
    virtual void paint(ProxyPaintObject &, View const & = OriginalView) {}

    /**
     * paint stuff onto "VideoViews" current picture
     * without touching it
     */
    virtual void paintOverlay(QPainter *) {}

    /**
    * getToolsFrame() will be called once at start up
    * to create a widget for gui with all
    * buttons needed for interaction
    */
    virtual std::shared_ptr<QWidget> getToolsWidget();

    /**
    * getParamsWidget() will be called once at start up
    * to create a widget for gui with all
    * parameter fields needed
    */
    virtual std::shared_ptr<QWidget> getParamsWidget();

    /**
     * @brief grabbedKeys() has to return a set of all keys that the
     * algorithms needs access to. All KeyEvents with keys in the set will
     * be forwarded to the algorithm
     * @return const reference to the set of keys
     */
    virtual std::set<Qt::Key> const &grabbedKeys() const;

    /**
     * @brief prepareSave() is called once before the serialization of
     * _trackedObjects. It should store or discard all temporary values
     * that are related to tracked Objects.
     */
    virtual void prepareSave() {}

    /**
     * @brief postLoad() is called once after the tracked objects are
     * loaded from serialized data. It should do any postprocessing required.
     */
    virtual void postLoad() {}

    /**
     * @brief postConnect() is called once after the tracking algorithm has
     * been initialized and the signals have been connected. It can be used
     * to emit signals that only need to be emitted during object initialization.
     */
    virtual void postConnect() {}

    void loadObjects(std::vector<TrackedObject> const &objects);
    void loadObjects(std::vector<TrackedObject> &&objects);
    std::vector<TrackedObject> const &getObjects();

    boost::optional<Algorithm::Type> getType() const {
        return _type;
    }
    void setType(Algorithm::Type type) {
        _type = type;
    }

    int getCurrentFrameNumber() const {
        return _currentFrameNumber;
    }

    int getMaxFrameNumber() const {
        return _maxFrameNumber;
    }

    float getCurrentZoomLevel() const {
        return _currentZoomLevel;
    }

  public Q_SLOTS:
    /**
    * receive Signal to set current frame number
    */
    void setCurrentFrameNumber(int frameNumber) {
        _currentFrameNumber = frameNumber;
    }

    /**
    * receive Signal to set maximum frame number
    */
    void setmaxFrameNumber(int maxFrameNumber) {
        _maxFrameNumber = maxFrameNumber;
    }

    /**
    * receive current zoom level from VideoView
    */
    void setZoomLevel(float zLevel) {
        _currentZoomLevel = zLevel;
    }

    /**
    * receive current image from TrackingThread
    */
    void setCurrentImage(cv::Mat img) {
        _currentImage = img;
    }

    /**
    * receive current video mode from gui
    */
    void setCurrentVideoMode(GUIPARAM::VideoMode videoMode) {
        _videoMode = videoMode;
    }


  Q_SIGNALS:
    /**
    * send a message to the GUI.
    */
    void notifyGUI(std::string message,
                   MSGS::MTYPE type = MSGS::MTYPE::NOTIFICATION);

    /**
    * send signal to VideoView and update display
    */
    void update();

    cv::Mat requestCurrentScreen();

    void forceTracking();

    void registerViews(const std::vector<View> views);

    /**
     * start/pause playback
     */
    void pausePlayback(bool paused);

    /**
     * seek in framesequence
     * @param framenumber where you want to jump to
     */
    void jumpToFrame(int framenumber);

  protected:
    Settings &_settings;
    std::vector<TrackedObject> _trackedObjects;

    GUIPARAM::VideoMode getVideoMode() {
        return _videoMode;
    }

    bool event(QEvent *event) override;

    /**
     * @return either a copy of the current frame image, wrapped in a
     * boost::optional, or a unintialized boost::optional, if there is no
     * frame yet
     */
    boost::optional<cv::Mat> getCurrentImageCopy() const;

    /**
    * will receive QMouseEvent as soon
    * as mouse is getting moved in video view
    */
    virtual void mouseMoveEvent(QMouseEvent * /* e */) {}

    /**
    * will receive QMouseEvent as soon
    * as any mouse button is pressed in video view
    */
    virtual void mousePressEvent(QMouseEvent * /* e */) {}

    /**
    * will receive QMouseEvent as soon
    * as any mouse button is released in video view
    */
    virtual void mouseReleaseEvent(QMouseEvent * /* e */) {}

    /**
    * will receive QMouseEvent as soond
    * as mouse wheel is activated in video view
    */
    virtual void mouseWheelEvent(QWheelEvent * /* e */) {}


    /**
    * will receive QKeyEvent as soon
    * as any keyboard key from 'grabbedKeys()' is pressed in video view
    */
    virtual void keyPressEvent(QKeyEvent * /* e */) {}


  private:
    int _currentFrameNumber;
    int _maxFrameNumber;
    float _currentZoomLevel;
    boost::optional<Algorithm::Type> _type;
    boost::optional<cv::Mat> _currentImage;
    GUIPARAM::VideoMode _videoMode;
};

#endif // !TrackingAlgorithm_H
