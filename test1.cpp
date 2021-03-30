#include <iostream>


#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/dnn.hpp>

#include "src/encounterdetector.h"
#include "src/config.h"

cv::Scalar drawColor = RED;



int main() {
    std::cout << "OpenCV Version: " + cv::getVersionString() << std::endl;
    cv::Mat frame;
    cv::VideoCapture cap;

    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    cap.open(deviceID, apiID);
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, Config::width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, Config::height);
    cap.set(cv::CAP_PROP_FPS, Config::fps);


    std::cout << cap.getBackendName() << std::endl;
    std::cout << "Dims: " << frame.dims << std::endl;
    std::cout << "Size: " << frame.size << std::endl;

    EncounterProtector process(Config::height);

    cv::Rect r(0, 0, static_cast<int>(Config::width), static_cast<int>(Config::height));
    cv::Rect r2(20, 20, 100, 100);

    //--- GRAB AND WRITE LOOP
    std::cout << "Start grabbing" << std::endl
        << "Press any key to terminate" << std::endl;
    for (size_t i = 0;; i++)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);

        if (process(frame)) {
            cv::rectangle(frame, r, rgb(0, 255, 0), 15);
        }
        else {
            cv::rectangle(frame, r, rgb(255, 0, 0), 5);
        }


        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        // show live and wait for a key with timeout long enough to show images
        cv::imshow("Live", frame);
        if (i == 0) {
            cv::moveWindow("Live", 4000, 200);
        }

        if (cv::waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}