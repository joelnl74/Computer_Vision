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

	cv::line(image, corner, projectedPoints[0], (1, 0, 0), 2);
	cv::line(image, corner, projectedPoints[1], (0, 1, 0), 2);
	cv::line(image, corner, projectedPoints[2], (0, 0, 1), 2);

	imshow("Display Window", image);

	cv::waitKey(0);
	
	return 0;
}