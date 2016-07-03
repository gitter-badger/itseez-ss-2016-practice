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
    IFrameSource* frameSource;
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
    IFrameProcessor* processor = createThresholdProcessor_OpenCV();

    // Main processing loop
    while(true)
    {
        // Get next frame
        Mat image = frameSource->getFrame();
        if (image.empty())
        {
            cout << "Image is empty. Aborting!" << endl;
            exit(0);
        }

        // Process frame
        Mat output = processor->process(image);

        // Show result, exit on any key pressed
        imshow("Output", output);
        const int waiting_time = parser.has("image") ? 1000 : 30;
        if (waitKey(waiting_time) != -1) // Break on any key
            return 0;
    }

    return 0;
}
