#include "include/frame_processor.hpp"

#include <memory>

#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

class ThresholdProcessor_OpenCV : public IFrameProcessor {
 public:
  ThresholdProcessor_OpenCV(int threshold) : threshold_(threshold) {}

  Mat Process(const Mat& input) {
    Mat gray;
    cvtColor(input, gray, CV_BGR2GRAY);
    threshold(gray, gray, 128, 255, THRESH_BINARY);
    return gray;
  }

 protected:
  int threshold_;
};

class ThresholdProcessor_Manual : public IFrameProcessor {
 public:
  ThresholdProcessor_Manual(int threshold) : threshold_(threshold) {}

  Mat Process(const Mat& input) {
    Mat gray;
    cvtColor(input, gray, CV_BGR2GRAY);
    Threshold(gray.data, gray.cols, gray.rows, 128);
    return gray;
  }

 protected:
  void Threshold(unsigned char* data, int width, int height,
                 int threshold) const {
    // TODO: implement threshold function here.
    for (size_t i = 0; i < static_cast<size_t>(width * height); ++i) {
      data[i] = (data[i] < threshold) ? 0 : 255;
    }
  }

  int threshold_;
};

// Factory methods for all processors.
shared_ptr<IFrameProcessor> createThresholdProcessor_OpenCV(int threshold) {
  return make_shared<ThresholdProcessor_OpenCV>(threshold);
}

shared_ptr<IFrameProcessor> createThresholdProcessor_Manual(int threshold) {
  return make_shared<ThresholdProcessor_Manual>(threshold);
}
