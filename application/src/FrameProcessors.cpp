#include "IFrameProcessor.hpp"

#include <opencv2/imgproc/imgproc.hpp>

class ThresholdProcessor_OpenCV: public IFrameProcessor {
 public:
    cv::Mat process(cv::Mat input) {
        cv::Mat gray;
        cvtColor(input, gray, CV_BGR2GRAY);
        threshold(gray, gray, 128, 255, cv::THRESH_BINARY);
        return gray;
    }
};

class ThresholdProcessor_Manual: public IFrameProcessor {
 public:
    cv::Mat process(cv::Mat input) {
        cv::Mat gray;
        cvtColor(input, gray, CV_BGR2GRAY);

        for(int row = 0; row < gray.rows; row++)
            for(int col = 0; col < gray.cols; col++)
            {
                // TODO: edit loop body properly
                gray.at<uchar>(row, col) = 128;
            }

        return gray;
    }
};

// Factory methods for each processor
std::shared_ptr<IFrameProcessor> createThresholdProcessor_OpenCV() {
    return std::shared_ptr<IFrameProcessor>(new ThresholdProcessor_OpenCV());
}

std::shared_ptr<IFrameProcessor> createThresholdProcessor_Manual() {
    return std::shared_ptr<IFrameProcessor>(new ThresholdProcessor_Manual());
}
