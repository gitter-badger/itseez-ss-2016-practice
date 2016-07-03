# pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class IFrameSource
{
 public:
     virtual cv::Mat getFrame() = 0;
};

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
