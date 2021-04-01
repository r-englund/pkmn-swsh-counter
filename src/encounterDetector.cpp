#include "encounterDetector.h"

#include <chrono>

#include "config.h"


std::string now() {

    auto nowt = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::to_time_t(nowt);

    std::string datetime = "YYYY-mm-dd_hh-mm-ss";
    std::strftime(datetime.data(), datetime.size()+1, "%Y-%m-%d_%H-%M-%S", localtime(&now));
    return datetime;
}



EncounterProtector::EncounterProtector(double height) :
    basePath{ "c:/temp/pkmlog/" },
    startRow{ static_cast<int>(864 * Config::scale) },
    endRow{ static_cast<int>(height - 32 * Config::scale) },
    emark{ rescale(cv::imread("C:/temp/opencv/test3/templates/emark.png")) },
    encounter{ rescale(cv::imread("C:/temp/opencv/test3/templates/enconter.png")) }
{

    std::string n = now();
    std::cout << n << std::endl;

    logStream.open(basePath + "log-" + n + ".txt");
    encountersStream.open(basePath + "encounters-" + n + ".txt");

    if (!logStream.good()) {
        throw std::exception("Failed to open file for writing");
    }

    if (!encountersStream.good()) {
        throw std::exception("Failed to open file for writing");
    }

}


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

                    foundEncounter(res);

                    std::cout << res << std::endl;
                }
                return true;
            }
        }


    }

    return false;

}

template<typename A, typename B>
B min(A a, B b) {
    if (a < b)
        return a;
    else return b;
}

void EncounterProtector::foundEncounter(std::string pkm) {
    auto n = now();

    log.emplace_back(pkm, n);

    std::cout << pkm << " " << n << std::endl;
    logStream << pkm << " " << n << std::endl;
    encountersStream << pkm << std::endl;


    count[pkm]++;

    {
        std::ofstream o(basePath + "last.txt");
        size_t i = 10;
        std::set<std::string> found;
            for (auto it = log.rbegin(); it != log.rend() && i > 0; ++it) {
                auto p = it->first;
                if (found.count(p) == 0) {
                    i--;
                    found.insert(p);
                    o << p << " #" << count[p] << std::endl;
                }
            }
    }


}