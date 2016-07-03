#include "IFrameSource.hpp"

#include <iostream>
#include <opencv2/highgui/highgui.hpp>

class ImageFrameSource: public IFrameSource
{
 public:
    ImageFrameSource(std::string path_to_image) {
        image_ = cv::imread(path_to_image);
    }

    cv::Mat getFrame() {
        // We allow to read image only once
        if (!image_.empty())
        {
            cv::Mat clone = image_.clone();
            image_ = cv::Mat();
            return clone;
        }
        else
        {
            return image_;
        }
    }

 private:
     cv::Mat image_;
};

class CameraFrameSource: public IFrameSource
{
 public:
    CameraFrameSource() {
        camera_.open(0);

        if (!camera_.isOpened())
        {
            std::cout << "Capture from camera 0 didn't work. Aborting." << std::endl;
            exit(0);
        }
    }

    cv::Mat getFrame() {
        cv::Mat frame;
        camera_ >> frame;
        return frame;
    }

 private:
     cv::VideoCapture camera_;
};

std::shared_ptr<IFrameSource> createImageFrameSource(std::string path) {
    return std::shared_ptr<IFrameSource>(new ImageFrameSource(path));
}

std::shared_ptr<IFrameSource> createCameraFrameSource() {
    return std::shared_ptr<IFrameSource>(new CameraFrameSource());
}
