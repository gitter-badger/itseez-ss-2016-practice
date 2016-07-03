#include "IFrameProcessor.hpp"

#include <opencv2/imgproc/imgproc.hpp>

class ToGrayscaleProcessor: public IFrameProcessor {
 public:
    cv::Mat process(cv::Mat input) {
        cv::Mat gray;
        cvtColor(input, gray, CV_BGR2GRAY);
        return gray;
    }
};

IFrameProcessor* createToGrayscaleProcessor()
{
    return new ToGrayscaleProcessor();
}
