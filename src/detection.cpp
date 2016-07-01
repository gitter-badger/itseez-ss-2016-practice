#include "detection.hpp"

#include <algorithm>
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"

using namespace cv;
using namespace std;

shared_ptr<Detector> Detector::CreateDetector(const string& name) {
  if (name == "cascade") {
    return std::make_shared<CascadeDetector>();
  } else if (name == "hog") {
    return std::make_shared<HOGDetector>();
  } else {
    cerr << "Failed to create detector with name '" << name << "'" << endl;
  }
  return nullptr;
}

bool CascadeDetector::Init(const string& model_file_path) {
  return detector.load(model_file_path);
}

void CascadeDetector::Detect(const Mat& frame, vector<Rect>& objects,
                             vector<double>& scores) {
  CV_Assert(!frame.empty());
  if (!detector.empty()) {
    vector<int> object_hits;
    const double kScaleFactor = 1.1;
    const int kMinHitsNum = 3;
    detector.detectMultiScale(frame, objects, object_hits, kScaleFactor,
                              kMinHitsNum);
    scores.resize(object_hits.size());
    copy(object_hits.begin(), object_hits.end(), scores.begin());
  } else {
    cerr << "Detector has not been initialized before usage." << endl;
  }
}

bool HOGDetector::Init(const string& model_file_path) {
  if (model_file_path == "people_default") {
    detector.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    return true;
  }
  if (model_file_path == "people_daimler") {
    detector.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
    return true;
  }
  return detector.load(model_file_path);
}

void HOGDetector::Detect(const Mat& frame, vector<Rect>& objects,
                         vector<double>& scores) {
  CV_Assert(!frame.empty());
  if (!detector.svmDetector.empty()) {
    const double kHitThreshold = 0.0;
    detector.detectMultiScale(frame, objects, scores, kHitThreshold);
  } else {
    cerr << "Detector has not been initialized before usage." << endl;
  }
}
