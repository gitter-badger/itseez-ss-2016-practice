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
    "{ v video        |        | video to process         }"
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

    IFrameSource* frameSource = createImageFrameSource("/Users/kirill-kornyakov/Temp/pro-git.jpg");
    IFrameProcessor* processor = createToGrayscaleProcessor();

    while(true)
    {
        Mat image = frameSource->getFrame();
        if (image.empty())
        {
            cout << "Image is empty. Aborting." << endl;
            exit(0);
        }

        Mat output = processor->process(image);

        imshow("Output", output);
        waitKey(0);
    }

    return 0;
}
