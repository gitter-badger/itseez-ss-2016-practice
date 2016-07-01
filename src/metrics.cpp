#include "metrics.hpp"

#include <utility>

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

float PrecisionRecallEvaluator::IntersectionOverUnion(const Rect& r,
                                                      const Rect& p) {
  float intersection_area = (r & p).area();
  float union_area = r.area() + p.area() - intersection_area;
  float iou = union_area > 0 ? intersection_area / union_area : 0.0f;
  return iou;
}

PrecisionRecallEvaluator::PrecisionRecallEvaluator() {
  num_objects_ = 0;
  num_objects_found_ = 0;
  num_responses_ = 0;
  num_false_alarms_ = 0;
  num_frames_ = 0;
  threshold_ = 0.5f;
}

void PrecisionRecallEvaluator::UpdateMetrics(const vector<Rect>& guess,
                                             const vector<Rect>& ground_truth) {
  num_frames_++;
  num_objects_ += ground_truth.size();
  num_responses_ += guess.size();

  vector<bool> objects_detected(ground_truth.size(), false);
  vector<bool> correct_detections(guess.size(), false);

  for (size_t i = 0; i < ground_truth.size(); ++i) {
    const Rect& gt = ground_truth.at(i);
    for (size_t j = 0; j < guess.size(); ++j) {
      if (IntersectionOverUnion(guess.at(j), gt) >= threshold_) {
        objects_detected[i] = true;
        correct_detections[j] = true;
        break;
      }
    }
  }

  num_objects_found_ +=
      std::count(objects_detected.begin(), objects_detected.end(), true);
  num_false_alarms_ +=
      std::count(correct_detections.begin(), correct_detections.end(), false);
}

float PrecisionRecallEvaluator::GetDetectionRate() const {
  return num_objects_ == 0 ? 0.0f : num_objects_found_ /
                                        static_cast<float>(num_objects_);
}

float PrecisionRecallEvaluator::GetFalseAlarmRate() const {
  return num_responses_ == 0 ? 0.0f : num_false_alarms_ /
                                          static_cast<float>(num_responses_);
}
GroundTruthReader::GroundTruthReader(const string& filename) {
  FileStorage file_storage;
  try {
    is_opened_ = file_storage.open(filename, FileStorage::READ);
  } catch (exception) {
    cerr << "Failed to read ground truth file." << endl;
    is_opened_ = false;
  }
  if (is_opened_) {
    file_node_ = file_storage["objects"];
    is_opened_ = !(file_node_.empty() || file_node_.isNone());
    if (is_opened_) {
      file_node_iter_ = file_node_.begin();
    }
  }
}

bool GroundTruthReader::Next(vector<Rect>& rects) {
  if (!is_opened_ || file_node_iter_ == file_node_.end()) {
    rects.clear();
    return false;
  } else {
    ++file_node_iter_;
    Get(rects);
    return true;
  }
}

bool GroundTruthReader::Get(vector<Rect>& rects) {
  if (!is_opened_ || file_node_iter_ == file_node_.end()) {
    rects.clear();
    return false;
  } else {
    file_node_iter_ >> rects;
    return true;
  }
}

bool GroundTruthReader::IsOpen() const {
  return is_opened_;
}
