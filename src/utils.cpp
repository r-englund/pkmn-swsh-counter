#include "utils.h"

#include "config.h"

cv::Mat rescale(cv::Mat src) {
    cv::Mat res;
    cv::resize(src, res, cv::Size{ 0,0 }, Config::scale, Config::scale);
    return res;
}
