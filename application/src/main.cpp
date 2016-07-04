#include <iostream>
#include <memory>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "include/frame_processor.hpp"
#include "include/frame_source.hpp"

using namespace std;
using namespace cv;

const char* kAbout = "Main application for summer school 2016.";

const char* kOptions =
    "{ i image        | <none>       | image to process         }"
    "{ v video        | <none>       | process camera images    }"
    "{ c camera       | <none>       | process camera images    }"
    "{ t threshold    | 128          | threshold                }"
    "{ h ? help usage |              | print help message       }";

int main(int argc, const char** argv) {
  // Parse command line arguments.
  CommandLineParser parser(argc, argv, kOptions);
  parser.about(kAbout);

  // If help option is given, print help message and exit.
  if (parser.get<bool>("help")) {
    parser.printMessage();
    return 0;
  }

  // Create frame source.
  std::shared_ptr<IFrameSource> frame_source;
  if (parser.has("image")) {
    frame_source = createImageFrameSource(parser.get<string>("image"));
  } else if (parser.has("video")) {
    frame_source = createVideoFrameSource(parser.get<string>("video"));
  } else if (parser.has("camera")) {
    frame_source = createCameraFrameSource(parser.get<int>("camera"));
  } else {
    parser.printMessage();
    return 0;
  }

  // Create frame processor.
  std::shared_ptr<IFrameProcessor> processor =
      createThresholdProcessor_OpenCV(parser.get<int>("threshold"));

  // Main processing loop.
  while (true) {
    // Get next frame.
    Mat frame = frame_source->GetFrame();
    if (frame.empty()) {
      cout << "Frame is empty. Aborting!" << endl;
      break;
    }

    // Process frame.
    Mat output = processor->Process(frame);

    // Show result, exit on any key pressed.
    imshow("Output", output);
    const int waiting_time = parser.has("image") ? 0 : 30;
    // Break on any key.
    if (waitKey(waiting_time) != -1) {
      break;
    }
  }

  return 0;
}
