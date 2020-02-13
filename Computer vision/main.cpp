#include<iostream>
#include "OpenCV1.h";
#include <opencv2/calib3d/calib3d.hpp>

int main()
{
	int amount = 13;
	int currentImage = 0;
	bool read = true;
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

		auto corner = opencv.GetFirstCorner(currentImage);
		auto projectedPoints = opencv.GetAxesPoints(currentImage);

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
		currentImage++;
	}

	cv::waitKey(0);
	
	return 0;
}