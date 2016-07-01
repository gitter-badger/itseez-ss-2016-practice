#include "metrics.hpp"

#include <utility>

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

float PrecisionRecallEvaluator::IntersectionOverUnion(const Rect& r,
                                                      const Rect& p) const {
  float intersection_area = (r & p).area();
  float union_area = r.area() + p.area() - intersection_area;
  float iou = union_area > 0 ? intersection_area / union_area : 0.0f;
  return iou;
}

PrecisionRecallEvaluator::PrecisionRecallEvaluator() {
  num_correct_ = 0;
  num_responses_ = 0;
  num_objects_ = 0;
  threshold_ = 0.25f;
}

bool PrecisionRecallEvaluator::UpdateMetrics(const Rect& guess,
                                             const Rect& ground_truth) {
  if (guess != Rect()) {
    num_responses_++;
  }
  if (ground_truth != Rect()) {
    num_objects_++;
  }
  if (ground_truth == Rect() ||
      IntersectionOverUnion(guess, ground_truth) >= threshold_) {
    num_correct_++;
    return true;
  }
  return false;
}

pair<float, float> PrecisionRecallEvaluator::GetMetrics() {
  return make_pair(
      num_responses_ == 0 ? 0.0f
                          : num_correct_ / static_cast<float>(num_responses_),
      num_objects_ == 0 ? 0.0f
                        : num_correct_ / static_cast<float>(num_objects_));
}

GroundTruthReader::GroundTruthReader(const string& filename) {
  FileStorage file_storage(filename);
  is_opened_ = file_storage.isOpened();
  if (is_opened_) {
    file_node_ = file_storage["objects"];
    is_opened_ = !(file_node_.empty() || file_node_.isNone());
    if (is_opened_) {
      file_node_iter_ = file_node_.begin();
    }
  }
  cout << "1" << endl;
  cout << is_opened_ << endl;
}

bool GroundTruthReader::Next(Rect& rect) {
  if (!is_opened_ || file_node_iter_ == file_node_.end()) {
    rect = Rect();
    cout << "2" << endl;
    return false;
  } else {
    ++file_node_iter_;
    get(rect);
    cout << "22" << endl;
    return true;
  }
}

bool GroundTruthReader::Get(Rect& rect) {
  if (!is_opened_ || file_node_iter_ == file_node_.end()) {
    rect = Rect();
    cout << "3" << endl;
    return false;
  } else {
    file_node_iter_ >> rect;
    cout << "33" << endl;
    return true;
  }
}

bool GroundTruthReader::IsOpen() const {
  return is_opened_;
}
