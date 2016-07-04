#pragma once

#include <memory>
#include <string>

#include <opencv2/core/core.hpp>

class IFrameSource {
 public:
  virtual cv::Mat GetFrame() = 0;
};

std::shared_ptr<IFrameSource> createImageFrameSource(
    const std::string& path_to_image);

std::shared_ptr<IFrameSource> createVideoFrameSource(
    const std::string& path_to_image);

std::shared_ptr<IFrameSource> createCameraFrameSource(int camera_id);
