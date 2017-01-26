#include "PStateInitial.h"
#include "Model/MediaPlayer.h"

PStateInitial::PStateInitial(MediaPlayer *player,
                             std::shared_ptr<BioTracker::Core::ImageStream> imageStream) :
    IPlayerState(player, imageStream) {
    operate();
}

void PStateInitial::operate() {

    m_Play = false;
    m_Forw = false;
    m_Back = false;
    m_Stop = false;
    m_Paus = false;

    //m_Mat = new cv::Mat(320, 320, CV_32F);
    m_FrameNumber = 0;

  //  Q_EMIT emitStateDone();

    m_Player->setNextState(IPlayerState::STATE_WAIT);
}