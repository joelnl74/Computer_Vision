#include<iostream>
#include "OpenCV1.h";
#include <opencv2/calib3d/calib3d.hpp>

int main()
{
	// AMOUNT OF IMAGES IN ROOT FOLDER
	int amount = 13;
	// CURRENT IMAGE SHOWING TO THE USER
	int currentImage = 0;
	// SHOULD WE READ FROM FILE IF YES READ FROM FILE FALSE CALIBRATE CAMERA FIRST
	bool read = true;
	// IMAGES ROOT FOLDER
	std::string imagesRootFolder = "images/";

	// Do the offline part of the assingement.
	OpenCV1 opencv;
	opencv.CalibrateCamera(amount, imagesRootFolder, read);

	while (currentImage < amount)
	{
		std::string currentImageToLoad = imagesRootFolder;
		currentImageToLoad.append(std::to_string(currentImage));
		currentImageToLoad.append(".jpg");

		cv::Mat image = cv::imread(currentImageToLoad);

		// Gets the first sqaure in the world.
		auto corner = opencv.GetFirstCorner(currentImage);
		// retrives the projected points 2d => 3d so we can draw the axis and the cube
		auto projectedPoints = opencv.GetAxesPoints(currentImage);

		// BOTTEM CUBE.
		cv::line(image, projectedPoints[3], projectedPoints[4], cv::Scalar(255, 0, 0), 2);
		cv::line(image, projectedPoints[3], projectedPoints[5], cv::Scalar(255, 0, 0), 2);
		cv::line(image, projectedPoints[3], projectedPoints[6], cv::Scalar(255, 0, 0), 2);
		cv::line(image, projectedPoints[7], projectedPoints[5], cv::Scalar(255, 0, 0), 2);

		// TOP CUBE.
		cv::line(image, projectedPoints[6], projectedPoints[8], cv::Scalar(255, 0, 0), 2);
		cv::line(image, projectedPoints[6], projectedPoints[9], cv::Scalar(255, 0, 0), 2);
		cv::line(image, projectedPoints[10], projectedPoints[9], cv::Scalar(255, 0, 0), 2);
		cv::line(image, projectedPoints[10], projectedPoints[8], cv::Scalar(255, 0, 0), 2);

		// CONNECTIONS BETWEEN TOP AND BOTTEM.
		cv::line(image, projectedPoints[4], projectedPoints[8], cv::Scalar(255, 0, 0), 2);
		cv::line(image, projectedPoints[7], projectedPoints[10], cv::Scalar(255, 0, 0), 2);
		cv::line(image, projectedPoints[5], projectedPoints[9], cv::Scalar(255, 0, 0), 2);
		cv::line(image, projectedPoints[4], projectedPoints[7], cv::Scalar(255, 0, 0), 2);

		// DRAW AXIS POINT.
		cv::line(image, corner, projectedPoints[0], cv::Scalar(255, 0, 0), 2);
		cv::line(image, corner, projectedPoints[1], cv::Scalar(0, 255, 0), 2);
		cv::line(image, corner, projectedPoints[2], cv::Scalar(0, 0, 255), 2);

		// SHOW IMAGE WITH DRAWN AXIS AND CUBE.
		imshow("Display Window", image);

		// WAIT FOR INPUT
		cv::waitKey(0);

		// GO ON TO THE NEXT IMAGE.
		currentImage++;
	}

	cv::waitKey(0);
	
	return 0;
}