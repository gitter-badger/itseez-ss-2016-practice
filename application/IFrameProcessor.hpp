#include <opencv2/core/core.hpp>

class IFrameProcessor {
 public:
    virtual cv::Mat process(cv::Mat input) =0;
};

IFrameProcessor* createThresholdProcessor_OpenCV();
IFrameProcessor* createThresholdProcessor_Manual();
