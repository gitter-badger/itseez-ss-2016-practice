#pragma once

#include <opencv2/core/core.hpp>

class IFrameSource
{
 public:
     virtual cv::Mat getFrame() = 0;
};

std::shared_ptr<IFrameSource> createImageFrameSource(std::string path_to_image);
std::shared_ptr<IFrameSource> createCameraFrameSource();
