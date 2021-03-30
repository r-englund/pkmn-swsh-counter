#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

class TextRecognizer {
public:

    cv::dnn::TextRecognitionModel recognizer_;

    TextRecognizer();
    std::string rec(cv::Mat& img);
};


