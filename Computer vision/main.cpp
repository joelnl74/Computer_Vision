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
	calibration.DrawFrameAxes(image);
	cv::rectangle(image, cv::Rect2i(corner.x, corner.y, 50, 50), cv::Scalar(255, 0, 0, 0), 4);
	//calibration.ReturnProjecttionPoint();

	//cv::line(image, corner, projectionPoints[0], cv::Scalar(255, 0, 0), 5);
	//cv::line(image, corner, projectionPoints[1], cv::Scalar(0, 255, 0), 5);
	//cv::line(image,corner,	projectionPoints[2], cv::Scalar(0, 0, 255), 5);

	// Do the online part for each image/frame
	//cv::rectangle(image, cv::Rect(0, 0, 50, 50), cv::Scalar(0, 255, 128));

	imshow("Display Window", image);

	cv::waitKey(0);
	
	return 0;
}