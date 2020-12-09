//
// Created by krook on 11/29/20.
//

#ifndef LICENSEPLATE_LICENSEPLATEDETECTION_H
#define LICENSEPLATE_LICENSEPLATEDETECTION_H

#include "Includes.h"

class LicensePlateDetection {
public:

    void detect();

    void preprocess();

    LicensePlateDetection(const std::string &path);

    std::string result();

private:
    std::string _result;
    std::string path;
    cv::Mat img;
    cv::Mat gray;
    cv::Mat edges;
    cv::Mat masked;
    cv::Mat cropped;
    std::vector<std::vector<cv::Point>> contours;

    void findContours();

    void maskImage() const;

    void maskImage();
};


#endif //LICENSEPLATE_LICENSEPLATEDETECTION_H
