//
//  main.cpp
//  LicensePlate
//
//  Created by Geszti Bence on 2020. 11. 18..
//

#include "LicensePlateDetection.h"
#include "Includes.h"

using namespace cv;

void first();

int main(int argc, const char *argv[]) {
    std::vector<std::string> files = {
            "IUK130.jpeg",
            "SET308.jpeg",
            "RJE091.jpeg",
            "HAB423.jpeg",
    };

    for (auto s : files) {
        LicensePlateDetection lpd(s);
        lpd.detect();
        std::cout << lpd.result() << std::endl;
        waitKey();
    }

    return 0;
}

