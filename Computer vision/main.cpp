#include<opencv2/opencv.hpp>
#include<iostream>

int main()
{
	cv::Mat image = cv::imread("jpg-vs-jpeg.jpg");
	cv::FileStorage fs("path here", cv::FileStorage::READ);
	cv::Mat intrinsics, distortion;
	fs["camera_matrix"] >> intrinsics;
	fs["distortion_coefficients"] >> distortion;

    if (image.empty())                      
    {
        std::cout << "Could not open or find the image" << std::endl;
    }
	else
	{
		cv::rectangle(image, cv::Rect(0, 0, 100, 100), cv::Scalar(0, 255, 128));
		imshow("Display Window", image);
	}
	std::vector<cv::Point3f> boardPoints;
	bool found = cv::findChessboardCorners(image, cv::Size(8, 9), boardPoints, cv::CALIB_CB_ADAPTIVE_THRESH);



	cv::waitKey(0);

	return 0;
}