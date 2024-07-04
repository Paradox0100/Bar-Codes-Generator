#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include "code39.h"
#include "imgGenerator.h"

int generateCode39IMG(std::wstring content, std::string path, std::string unencoded) {

    //std::wstring content = L"| |▮▮|▮ ▮||||▮| ▮|▮||| ▮|▮| ▮||▮▮| |▮|▮ ||||▮ |▮|▮| ▮|▮|| |▮| |▮▮|";

    int totalWidth = 0;
    int counter = 0;

    for (wchar_t c : content) {
        if (c == L'▮' && counter % 2 == 0) {
            totalWidth += 3;
        } else if (c == L'▮' && counter % 2 != 0) {
            totalWidth += 6;
            counter++;
        } else if (c == L'|' && counter % 2 == 0) {
            totalWidth += 1;
        } else if (c == L'|' && counter % 2 != 0) {
            totalWidth += 4;
            counter++;
        } else if (c == L' ') {
            totalWidth += 6;
        }
        counter++;
    }

    //std::cout << "total width: " << totalWidth << std::endl;

    cv::Mat image(150, totalWidth+50, CV_8UC3, cv::Scalar(255, 255, 255));

    // Draw a bar on the image

    int barWidth = 0;
    int barHeight = 100;
    int barX = 0;
    int barY = 25;

    int currentX = 25;
    counter = 0;
    for (wchar_t c : content) {
        int currentWidth;
        if (c == L'▮' && counter % 2 == 0) {
        barWidth = 3;
        barX = currentX;
        currentX += 3;
        cv::rectangle(image, cv::Point(barX, barY), cv::Point(barX + barWidth, barY + barHeight), cv::Scalar(0, 0, 0), -1);
    } else if (c == L'▮' && counter % 2 != 0) {
        //std::cout << "narrow gap\n";
        currentX += 3;
        barWidth = 3;
        barX = currentX;
        currentX += 3;
        counter++;
        cv::rectangle(image, cv::Point(barX, barY), cv::Point(barX + barWidth, barY + barHeight), cv::Scalar(0, 0, 0), -1);
    } else if (c == L'|' && counter % 2 == 0) {
        barWidth = 1;
        barX = currentX;
        currentX += 1;
        cv::rectangle(image, cv::Point(barX, barY), cv::Point(barX + barWidth, barY + barHeight), cv::Scalar(0, 0, 0), -1);
    } else if (c == L'|' && counter % 2 != 0) {
        //std::cout << "narrow gap\n";
        currentX += 3;
        barWidth = 1;
        barX = currentX;
        currentX += 1;
        counter++;
        cv::rectangle(image, cv::Point(barX, barY), cv::Point(barX + barWidth, barY + barHeight), cv::Scalar(0, 0, 0), -1);
    } else if (c == L' ') {
        currentX += 6;
    }
        counter++;
    }

    // add the unencoded string to the bottom

    cv::Point position;
    int font = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 0.4;
    cv::Scalar fontColor(0, 0, 0);
    int thickness = 1;
    int baseline = 0;
    cv::Size size = cv::getTextSize(unencoded, font, fontScale, thickness, &baseline);
    position.x = (image.cols - size.width) / 2;
    position.y = (image.rows - ((25-size.height)/2));
    cv::putText(image, unencoded, position, font, fontScale, fontColor, thickness);


    cv::imwrite(path, image);

    return 0;
}