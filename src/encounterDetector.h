#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>


#include "textrecognizer.h"
#include "utils.h"


struct EncounterProtector {


    TextRecognizer textRecognizer;

    cv::Mat emark;
    cv::Mat encounter;

    int startRow;
    int endRow;

    bool prev = false;

    EncounterProtector(double height);

    bool operator() (cv::Mat& frame) {
        auto res = functor(frame);
        prev = res;
        return res;
    }
private:
    cv::Mat_<float> scoreFrame;
    cv::Mat_<float> scoreFrame2;
    bool functor(cv::Mat& frame);
};
