#include "include/frame_processor.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"

using namespace cv;
using namespace std;

class MedianFlowTracker : public IFrameProcessor {
 public:
  MedianFlowTracker(const Mat& initial_frame, const Rect& initial_location) {
    location_ = initial_location;
    frame_ = initial_frame.clone();
    Rect image_boundaries(Point(), frame_.size());
    if ((image_boundaries & location_) != location_) {
      cerr << "Error. Initial location is outside of the frame." << endl;
      location_ = Rect();
      frame_ = Mat();
    }
  }

  Mat Process(const Mat& new_frame) {
    if (new_frame.empty()) {
      cerr << "Error. Empty image." << endl;
      return Mat();
    }

    if (location_ == Rect()) {
      cout << "Warning. Tracker is not initialized." << endl;
      return new_frame;
    }

    // TODO: implement tracking logic here.
    Rect current_location = location_;

    const Scalar kColorRed = CV_RGB(255, 0, 0);
    const int kLineThickness = 3;
    Mat image = new_frame.clone();
    rectangle(image, current_location, kColorRed, kLineThickness);
    return image;
  }

 protected:
  Rect location_;
  Mat frame_;
};

shared_ptr<IFrameProcessor> createMedianFlowTracker(
    const Mat& initial_frame, const Rect& initial_location) {
  return make_shared<MedianFlowTracker>(initial_frame, initial_location);
}
