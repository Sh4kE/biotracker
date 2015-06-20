#pragma once

#include <QMainWindow>

#include "source/core/Facade.h"
#include "source/gui/ui_MainWindow.h"
#include "source/gui/AlgorithmSelectionWidget.h"
#include "source/gui/NotificationWidget.h"
#include "source/gui/VideoControlWidget.h"
#include "source/gui/VideoView.h"
#include "source/util/QtRaiiWrapper.hpp"

namespace BioTracker {
namespace Gui {

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    typedef Util::QtRaiiWrapper<Ui::MainWindow, QMainWindow> MainWindowUi;

    MainWindow(Core::Facade &facade);

    const MainWindowUi& getUi() const { return m_ui; }

    const VideoView& getVideoView() const { return m_videoView; }
    const AlgorithmSelectionWidget& getAlgorithmSelection() const { return m_algorithmSelection; }
    const NotificationWidget& getNotification() const { return m_notification; }
    const VideoControlWidget& getVideoControl() const { return m_videoControl; }

private:
    MainWindowUi m_ui;
    AlgorithmSelectionWidget m_algorithmSelection;
    NotificationWidget m_notification;
    VideoControlWidget m_videoControl;
    VideoView m_videoView;
};



}
}