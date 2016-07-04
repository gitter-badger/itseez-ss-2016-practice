#pragma once

#include <memory>
#include <string>

#include <opencv2/core/core.hpp>

class IFrameProcessor {
 public:
  virtual cv::Mat Process(const cv::Mat& input) = 0;
};

std::shared_ptr<IFrameProcessor> createThresholdProcessor_OpenCV(int threshold);
std::shared_ptr<IFrameProcessor> createThresholdProcessor_Manual(int threshold);
std::shared_ptr<IFrameProcessor> createCascadeDetector(const std::string& path);
std::shared_ptr<IFrameProcessor> createMedianFlowTracker(
    const cv::Mat& initial_frame, const cv::Rect& initial_location);
