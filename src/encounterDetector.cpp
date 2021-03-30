#include "encounterDetector.h"

#include "config.h"

EncounterProtector::EncounterProtector(double height) :
    startRow{ static_cast<int>(864 * Config::scale) },
    endRow{ static_cast<int>(height - 32 * Config::scale) },
    emark{ rescale(cv::imread("C:/temp/opencv/test3/templates/emark.png")) },
    encounter{ rescale(cv::imread("C:/temp/opencv/test3/templates/enconter.png")) }
{}


bool EncounterProtector::functor(cv::Mat& frame) {
    auto subFrame = frame.rowRange(startRow, endRow);

    auto col = subFrame.row(3);
    cv::Scalar mean, dev, diff;
    cv::meanStdDev(col, mean, dev);

    cv::absdiff(mean, cv::Scalar(49, 48, 45), diff);

    if (cv::sum(diff)[0] < 10) {
        cv::matchTemplate(subFrame, encounter, scoreFrame, cv::TM_CCOEFF_NORMED);
        auto [minV, maxV, minL, maxL] = minmax(scoreFrame);
        if (maxV > 0.95) {
            cv::matchTemplate(subFrame, emark, scoreFrame2, cv::TM_CCOEFF_NORMED);
            auto [minV2, maxV2, minL2, maxL2] = minmax(scoreFrame2);
            if (maxV2 > 0.94) {
                if (!prev) {
                    const int startCol2 = encounter.size[1] + maxL.x;
                    const int startRow2 = static_cast<int>(maxL.y - 8 * Config::scale);
                    const int endCol2 = maxL2.x;
                    const int endRow2 = static_cast<int>(startRow2 + encounter.size[0] + 16 * Config::scale);

                    auto pkmImage = subFrame.colRange(startCol2, endCol2).rowRange(startRow2, endRow2);

                    auto res = textRecognizer.rec(pkmImage);

                    std::cout << res << std::endl;
                }
                return true;
            }
        }


    }

    return false;

}