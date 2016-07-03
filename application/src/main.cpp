#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include "IFrameSource.hpp"
#include "IFrameProcessor.hpp"

using namespace std;
using namespace cv;

const char* kAbout =
    "This is an empty application that can be treated as a template for your "
    "own doing-something-cool applications.";

const char* kOptions =
    "{ i image        |        | image to process         }"
    "{ c camera       |        | process camera images    }"
    "{ h ? help usage |        | print help message       }";

int main(int argc, const char** argv)
{
    // Parse command line arguments
    CommandLineParser parser(argc, argv, kOptions);
    parser.about(kAbout);

    // If help option is given, print help message and exit
    if (parser.get<bool>("help"))
    {
        parser.printMessage();
        return 0;
    }

    // Create frame source
    std::shared_ptr<IFrameSource> frameSource;
    if (parser.has("image"))
        frameSource = createImageFrameSource(parser.get<string>("image"));
    else if (parser.has("camera"))
        frameSource = createCameraFrameSource();
    else
    {
        parser.printMessage();
        return 0;
    }

    // Create frame processor
    std::shared_ptr<IFrameProcessor> processor = createThresholdProcessor_OpenCV();

    // Main processing loop
    while(true)
    {
        // Get next frame
        Mat frame = frameSource->getFrame();
        if (frame.empty())
        {
            cout << "Frame is empty. Aborting!" << endl;
            break;
        }

        // Process frame
        Mat output = processor->process(frame);

        // Show result, exit on any key pressed
        imshow("Output", output);
        const int waiting_time = parser.has("image") ? 1000 : 30;
        if (waitKey(waiting_time) != -1) // Break on any key
            break;
    }

    return 0;
}
