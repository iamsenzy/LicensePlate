//
// Created by krook on 11/29/20.
//

#include "LicensePlateDetection.h"
#include "Includes.h"

/**
 * Get result of an instance.
 *
 * @return the license plate as a string
 */
std::string LicensePlateDetection::result() {
    if (!this->_result.empty()) {
        return this->_result;
    }

    return "There is no result as of yet.";
}

/**
 * Perform all necessary steps on `img` and populate `_result`;
 *
 * @param path
 * @populates _result
 */
void LicensePlateDetection::detect() {
    this->preprocess();
    this->findContours();
    this->maskImage();
}

/**
 * Convert to grayscale, apply Canny edge detection.
 */
void LicensePlateDetection::preprocess() {
    cv::blur(this->gray, this->edges, cv::Size(3, 3));
    cv::Canny(this->edges, this->edges, 30, 200, 3);
    cv::imshow("preprocess - 1", this->img);
    cv::imshow("preprocess - 2", this->gray);
    cv::imshow("preprocess - 3", this->edges);
}

void LicensePlateDetection::findContours() {
    std::vector<cv::Vec4i> hieararchy;
    cv::findContours(this->edges, this->contours, hieararchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // sort contours by their area so small ones get overlooked
    std::sort(this->contours.begin(), this->contours.end(),
              [](const std::vector<cv::Point> &c1, const std::vector<cv::Point> c2) {
                  return cv::contourArea(c1, false) > cv::contourArea(c2, false);
              });

    // we only need the first 50% of contours
    this->contours.resize(10);

    cv::Mat drawing = cv::Mat::zeros(this->edges.size(), CV_8UC1);
    cv::Scalar color = cv::Scalar(255, 255, 255);
    for (size_t i = 0; i < contours.size(); i++) {
        cv::drawContours(drawing, this->contours, (int) i, color, cv::LINE_4, 2, hieararchy, 0);
    }
    cv::imshow("findcontours - 1", drawing);

}

void LicensePlateDetection::maskImage() {
    // vector storing points of the rectangle-shaped object
    std::vector<cv::Point> approx;

    for (auto c : contours) { // find a contour that is closed and has a rectangle shape, there is room for improvement here
        int len = cv::arcLength(c, true);
        cv::approxPolyDP(c, approx, len * 0.018, true);
        if (approx.size() == 4) {
            // if a contour has 4 edges and has a rectangle shape, it is safe to assume that we found the license plate itself
            break;
        }
    }

    std::vector<std::vector<cv::Point>> contoursProbable = {approx};

    cv::Mat mask = cv::Mat::zeros(img.size(), CV_8UC1);
    cv::drawContours(mask, contoursProbable, 0, cv::Scalar(255, 255, 255), -1);
    cv::bitwise_and(img, img, masked, mask);
    cv::imshow("findcontours - 2", masked);
}

/**
 * Constructor.
 * @param path the path to the file
 */
LicensePlateDetection::LicensePlateDetection(const std::string &path) : path(path) {
    try {
        this->img = cv::imread(path, 1);
        cv::cvtColor(this->img, this->gray, cv::COLOR_BGR2GRAY);
    } catch (const int errno) {
        throw;
    }
}
