#pragma once


#include <opencv2/opencv.hpp>



const static auto BLUE = cv::Scalar(255, 0, 0);
const static auto RED = cv::Scalar(0, 0, 255);
const static auto GREEN = cv::Scalar(0, 255, 0);


template<typename T>
auto minmax(T& src, cv::InputArray mask = cv::noArray()) {
    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(src, &minVal, &maxVal, &minLoc, &maxLoc, mask);
    return std::make_tuple(minVal, maxVal, minLoc, maxLoc);

}


template<typename T>
cv::Scalar_<T> rgb(const T r, const T g, const T b) {
    return {
        b,g,r
    };
}

cv::Mat rescale(cv::Mat src);
