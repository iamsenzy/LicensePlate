//
//  main.cpp
//  LicensePlate
//
//  Created by Geszti Bence on 2020. 11. 18..
//

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
void first();

int main(int argc, const char * argv[]) {
    first();
    waitKey();
    return 0;
}

void first() {
    Mat img = imread("vegita.jpeg");
    
    imshow("Vegita", img);
}
