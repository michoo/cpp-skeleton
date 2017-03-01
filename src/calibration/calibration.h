//
// Created by fred on 30/07/16.
//

#ifndef OPENCV_TUTO_CALIBRATION_H
#define OPENCV_TUTO_CALIBRATION_H
#include "../utils/Common.h"

using namespace cv;

class Calibration {
public:
    void calibrate();

    struct Camera
    {
        cv::Mat CameraMatrix;
        cv::Mat ImagePoints;
        cv::Mat DistortionCoefficients;
        cv::Mat Image;
    };

    std::vector<Point3f> Create3DChessboardCorners(Size boardSize, float squareSize);
    Camera CalibrateCamera(Mat image);

};


#endif //OPENCV_TUTO_CALIBRATION_H
