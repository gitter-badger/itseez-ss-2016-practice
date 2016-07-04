#include "include/frame_source.hpp"

#include <iostream>
#include <memory>

#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class ImageFrameSource : public IFrameSource {
 public:
  ImageFrameSource(const string& path_to_image) {
    image_ = imread(path_to_image);
  }

  Mat GetFrame() {
    // We allow to read image only once.
    if (!image_.empty()) {
      Mat clone = image_.clone();
      image_ = cv::Mat();
      return clone;
    } else {
      return image_;
    }
  }

 protected:
  Mat image_;
};

class VideoFrameSource : public IFrameSource {
 public:
  VideoFrameSource(const string& path_to_video) {
    video_.open(path_to_video);
    if (!video_.isOpened()) {
      cout << "Failed to load video from file '" << path_to_video << "'."
           << endl;
      exit(0);
    }
  }

  Mat GetFrame() {
    Mat frame;
    video_ >> frame;
    return frame;
  }

 private:
  VideoCapture video_;
};

class CameraFrameSource : public IFrameSource {
 public:
  CameraFrameSource(int camera_id) {
    camera_.open(camera_id);
    if (!camera_.isOpened()) {
      cout << "Failed to capture video from camera #" << camera_id << endl;
      exit(0);
    }
  }

  Mat GetFrame() {
    Mat frame;
    camera_ >> frame;
    return frame;
  }

 private:
  VideoCapture camera_;
};

shared_ptr<IFrameSource> createImageFrameSource(const string& path) {
  return make_shared<ImageFrameSource>(path);
}

shared_ptr<IFrameSource> createVideoFrameSource(const string& path) {
  return make_shared<VideoFrameSource>(path);
}

shared_ptr<IFrameSource> createCameraFrameSource(int camera_id) {
  return make_shared<CameraFrameSource>(camera_id);
}
