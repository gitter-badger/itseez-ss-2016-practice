#pragma once

#include <vector>

#include "opencv2/opencv.hpp"

class PrecisionRecallEvaluator {
 protected:
  size_t num_objects_;
  size_t num_objects_found_;
  size_t num_responses_;
  size_t num_false_alarms_;
  size_t num_frames_;
  float threshold_;

 public:
  PrecisionRecallEvaluator();

  void UpdateMetrics(const std::vector<cv::Rect>& guess,
                     const std::vector<cv::Rect>& ground_truth);
  void UpdateMetrics(const std::vector<cv::Rect>& guess,
                     const std::vector<double>& scores,
                     const std::vector<cv::Rect>& ground_truth);

  float GetDetectionRate() const;
  float GetFalseAlarmRate() const;
  static float IntersectionOverUnion(const cv::Rect& r, const cv::Rect& p);
};

class GroundTruthReader {
 protected:
  cv::FileNode file_node_;
  cv::FileNodeIterator file_node_iter_;
  bool is_opened_;

 public:
  GroundTruthReader(const std::string& filename);
  bool Next(std::vector<cv::Rect>& rect);
  bool Get(std::vector<cv::Rect>& rect);
  bool IsOpen() const;
};
