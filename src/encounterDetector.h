#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>


#include "textrecognizer.h"
#include "utils.h"


#include <fstream>
#include <set>
#include <map>


struct EncounterProtector {


    TextRecognizer textRecognizer;

    std::string basePath;

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


    void foundEncounter(std::string pkm);

private:
    cv::Mat_<float> scoreFrame;
    cv::Mat_<float> scoreFrame2;
    bool functor(cv::Mat& frame);



    std::ofstream logStream;
    std::ofstream encountersStream;

    std::map<std::string, size_t> count;

    std::vector<std::pair<std::string, std::string>> log;



};
