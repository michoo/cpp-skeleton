//
// Created by fred on 30/07/16.
//

#include "calibration.h"
#include "../utils/Common.h"


using namespace cv;

void Calibration::calibrate() {

    VideoCapture cap(0);

    cap.open(0);

    if( !cap.isOpened() ) { // check if we succeeded
        LOG(ERROR) << "Couldn't open capture.";

    }

    cap.set(CAP_PROP_AUTOFOCUS, 1);

    cap.set(CV_CAP_PROP_FPS, 30);
    cap.set(CV_CAP_PROP_FOURCC,CV_FOURCC('M','J','P','G'));
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080.0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920.0);

    // Specify the number of squares along each dimension of the board.
    // This is actually the number of "inside corners" (where a black square meets a white square).
    // That is, if the board is composed of n x m squares, you would use (n-1, m-1) as the arguments.
    // For example, for a standard checkerboard (8x8 squares), you would use:
    Size boardSize(11,6);

    float squareSize = 2.54f; // This is "1 arbitrary unit"

    std::vector<std::vector<cv::Point2f>> imagePoints;

    std::vector<cv::Point2f> pointBuf;
    namedWindow( "Image View", 1 );
    Mat image, gray_image;
    cap >> image;
    Size imageSize = image.size();

    cap >> image;
    cvtColor(image, gray_image , cv::COLOR_BGR2GRAY);


    imshow("Image View", image);


    Camera cam = CalibrateCamera(gray_image);

    Mat imageUndistorted;
    while(1) {
        cap >> image;
        undistort(image, imageUndistorted, cam.CameraMatrix, cam.DistortionCoefficients);

        imshow("win1", image);
        imshow("win2", imageUndistorted);
        if( cv::waitKey(1) >= 0 ){
            break;
        }
    }


}

std::vector<Point3f> Calibration::Create3DChessboardCorners(Size boardSize, float squareSize)
{
    // This function creates the 3D points of your chessboard in its own coordinate system

    std::vector<Point3f> corners;

    for( int i = 0; i < boardSize.height; i++ )
    {
        for( int j = 0; j < boardSize.width; j++ )
        {
            corners.push_back(Point3f(float(j*squareSize),
                                      float(i*squareSize), 0));
        }
    }

    return corners;
}

Calibration::Camera Calibration::CalibrateCamera(Mat image)
{
    Size boardSize(11,6); // the number of "inside corners" (where a black square meets a white square). This board is actually 8x8 squares

    float squareSize = 2.54f; // This is "1 arbitrary unit"

    Size imageSize = image.size();

    // Find the chessboard corners
    std::vector<std::vector<Point2f> > imagePoints(1);
    bool found = findChessboardCorners(image, boardSize, imagePoints[0]);
    if(!found)
    {
        LOG(ERROR) << "Could not find chess board!";
        exit(-1);
    }

    drawChessboardCorners(image, boardSize, Mat(imagePoints[0]), found );

    std::vector<std::vector<Point3f> > objectPoints(1);
    objectPoints[0] = Create3DChessboardCorners(boardSize, squareSize);

    std::vector<Mat> rotationVectors;
    std::vector<Mat> translationVectors;

    Mat distortionCoefficients = Mat::zeros(8, 1, CV_64F); // There are 8 distortion coefficients
    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);

    int flags = 0;
    double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix,
                                 distortionCoefficients, rotationVectors, translationVectors, flags|CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);

    LOG(DEBUG) <<  "RMS: " << rms ;

    LOG(DEBUG) <<  "Camera matrix: " << cameraMatrix;
    LOG(DEBUG) <<  "Distortion _coefficients: " << distortionCoefficients;

    imshow("Image View", image);

    Camera camera;
    camera.CameraMatrix = cameraMatrix;
    camera.ImagePoints = Mat(imagePoints[0]);
    camera.DistortionCoefficients = distortionCoefficients;
    camera.Image = image;

    return camera;
}