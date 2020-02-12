#include<iostream>
#include "OfflineOpenCV.h";
#include <opencv2/calib3d/calib3d.hpp>
// https://www.programcreek.com/python/example/89414/cv2.projectPoints
// https://docs.opencv.org/3.4/d7/d53/tutorial_py_pose.html
// https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html#decomposeprojectionmatrix
// https://docs.opencv.org/master/d0/daf/group__projection.html

int main()
{
	// Do the offline part of the assingement.
	OfflineOpenCV calibration;
	calibration.CalibrateCamera();

	cv::Mat image = cv::imread("images/0.jpg");;

	auto corner = calibration.GetFirstCorner();
	auto projectedPoints = calibration.GetAxesPoints();

	// BOTTEM.
	cv::line(image, projectedPoints[3], projectedPoints[4], cv::Scalar(255, 0, 0), 2);
	cv::line(image, projectedPoints[3], projectedPoints[5], cv::Scalar(255, 0, 0), 2);
	cv::line(image, projectedPoints[3], projectedPoints[6], cv::Scalar(255, 0, 0), 2);
	cv::line(image, projectedPoints[7], projectedPoints[5], cv::Scalar(255, 0, 0), 2);

	// TOP.
	cv::line(image, projectedPoints[6], projectedPoints[8], cv::Scalar(255, 0, 0), 2);
	cv::line(image, projectedPoints[6], projectedPoints[9], cv::Scalar(255, 0, 0), 2);
	cv::line(image, projectedPoints[10], projectedPoints[9], cv::Scalar(255, 0, 0), 2);
	cv::line(image, projectedPoints[10], projectedPoints[8], cv::Scalar(255, 0, 0), 2);


	// Connection top to bottem.
	cv::line(image, projectedPoints[4], projectedPoints[8], cv::Scalar(255, 0, 0), 2);
	cv::line(image, projectedPoints[7], projectedPoints[10], cv::Scalar(255, 0, 0), 2);
	cv::line(image, projectedPoints[5], projectedPoints[9], cv::Scalar(255, 0, 0), 2);
	cv::line(image, projectedPoints[4], projectedPoints[7], cv::Scalar(255, 0, 0), 2);

	// Draw axis points.
	cv::line(image, corner, projectedPoints[0], cv::Scalar(255, 0, 0), 2);
	cv::line(image, corner, projectedPoints[1], cv::Scalar(0, 255, 0), 2);
	cv::line(image, corner, projectedPoints[2], cv::Scalar(0, 0, 255), 2);

	imshow("Display Window", image);

	cv::waitKey(0);
	
	return 0;
}