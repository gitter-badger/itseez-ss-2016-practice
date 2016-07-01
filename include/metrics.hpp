#pragma once

#include <vector>

#include "opencv2/opencv.hpp"

class PrecisionRecallEvaluator {
 protected:
  size_t num_correct_;
  size_t num_responses_;
  size_t num_objects_;
  float threshold_;

 public:
  PrecisionRecallEvaluator()
      : num_correct_(0), num_responses_(0), num_objects_(0) {
  }

  bool UpdateMetrics(const cv::Rect& guess, const cv::Rect& ground_truth) {
    if (guess != cv::Rect()) {
      num_responses_++;
    }
    if (ground_truth != cv::Rect()) {
      num_objects_++;
    }
    if (ground_truth == cv::Rect() ||
        IntersectionOverUnion(guess, ground_truth) >= 0.25f) {
      num_correct_++;
      return true;
    }
    return false;
  }

  std::pair<float, float> GetMetrics() {
    return std::make_pair(
        num_responses_ == 0 ? 0.0f
                            : num_correct_ / static_cast<float>(num_responses_),
        num_objects_ == 0 ? 0.0f
                          : num_correct_ / static_cast<float>(num_objects_));
  }

  static float IntersectionOverUnion(const cv::Rect& r,
                                     const cv::Rect& p) const {
    float intersection_area = (r & p).area();
    float union_area = r.area() + p.area() - intersection_area;
    float iou = union_area > 0 ? intersection_area / union_area : 0.0f;
    return iou;
  }
};

class GroundTruthReader {
 protected:
  cv::FileNode file_node_;
  cv::FileNodeIterator file_node_iter_;
  bool is_opened_;

 public:
  GroundTruthReader(const std::string& filename);
  bool Next(cv::Rect& rect);
  bool Get(cv::Rect& rect);
  bool IsOpen() const;
};
