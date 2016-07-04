#include "include/frame_processor.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"

using namespace cv;
using namespace std;

class CascadeDetector : public IFrameProcessor {
 public:
  CascadeDetector(const string& path) {
    try {
      detector_.load(path);
    } catch (exception) {
    }
  }

  Mat Process(const Mat& frame) {
    if (frame.empty()) {
      cerr << "Error. Empty image." << endl;
      return Mat();
    }
    if (detector_.empty()) {
      cerr << "Detector has not been initialized before usage." << endl;
      return Mat();
    }

    vector<int> object_hits;
    vector<Rect> objects;
    const double kScaleFactor = 1.1;
    const int kMinHitsNum = 3;
    detector_.detectMultiScale(frame, objects, object_hits, kScaleFactor,
                               kMinHitsNum);

    const Scalar kColorRed = CV_RGB(255, 0, 0);
    const int kLineThickness = 3;
    Mat image = frame.clone();
    for (const auto& r : objects) {
      rectangle(image, r, kColorRed, kLineThickness);
    }

    return image;
  }

 protected:
  CascadeClassifier detector_;
};

shared_ptr<IFrameProcessor> createCascadeDetector(const string& path) {
  return make_shared<CascadeDetector>(path);
}
