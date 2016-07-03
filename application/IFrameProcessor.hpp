#include <opencv2/core/core.hpp>

class IFrameProcessor {
 public:
    virtual cv::Mat process(cv::Mat input) =0;
};

IFrameProcessor* createToGrayscaleProcessor();
IFrameProcessor* createThresholdProcessor_OpenCV();
IFrameProcessor* createThresholdProcessor_Manual();
