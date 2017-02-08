#include "BioTrackerTrackingAlgorithm.h"

BioTrackerTrackingAlgorithm::BioTrackerTrackingAlgorithm(IModel *parameter)
{
    m_TrackingParameter = parameter;
//    setTrackedComponentFactory(factory);
}

void BioTrackerTrackingAlgorithm::doTracking(std::shared_ptr<cv::Mat> image, uint framenumber)
{
    int i = 10;
    int y = 15;
    int z = i + y;

    std::shared_ptr<cv::Mat> mat(new cv::Mat);
    cv::applyColorMap(*image.get(), *mat.get(), cv::COLORMAP_JET);


    Q_EMIT emitCvMatA(mat, QString("tracker"));

    QString str;
    str.resize(6);
    for (int s = 0; s < 6 ; ++s) {
        str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));
    }

    Q_EMIT emitTrackingDone();

//    m_TrackedElement = dynamic_cast<TrackedElement *>(m_TrackedComponentFactory->getNewTrackedElement());
//    m_TrackedElement->setObjectName(str);


}
