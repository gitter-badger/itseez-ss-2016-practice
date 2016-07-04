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
  MedianFlowTracker() {
    // TODO: implement.
  }

  Mat Process(const Mat& frame, const Rect& previous_location) {
    if (frame.empty()) {
      cerr << "Error. Empty image." << endl;
      return Mat();
    }

    // TODO: implement tracking logic here.
    Rect current_location = previous_location;

    const Scalar kColorRed = CV_RGB(255, 0, 0);
    const int kLineThickness = 3;
    Mat image = frame.clone();
    rectangle(image, current_location, kColorRed, kLineThickness);
    return image;
  }
};
