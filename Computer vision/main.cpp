#include<iostream>
#include "OfflineOpenCV.h";
// https://www.programcreek.com/python/example/89414/cv2.projectPoints
// https://docs.opencv.org/3.4/d7/d53/tutorial_py_pose.html
// https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html#decomposeprojectionmatrix
// https://docs.opencv.org/master/d0/daf/group__projection.html

int main()
{
	// Do the offline part of the assingement.
	OfflineOpenCV calibration;
	calibration.CalibrateCamera();

	// Do the online part for each image/frame
	//cv::Mat image;
	//cv::line(image, cv::Point2f(0, 0), cv::Point2f(50, 0), cv::Scalar(255, 0, 0), 5);
	//cv::line(image, cv::Point2f(0, 0), cv::Point2f(0, 50), cv::Scalar(0, 255, 0), 5);
	//cv::line(image, cv::Point2f(0, 0), cv::Point2f(50, 50), cv::Scalar(0, 0, 255), 5);


	/*
	int squareSize = 0;
	cv::Mat image = cv::imread("calib-checkerboard.png");
	cv::Mat camera_matrix, extrinsives, imagePoints, gridPoints, distortionCoefficients;
	std::vector<cv::Point3f> boardPoints;
	cv::FileStorage fs("out_camera_data.xml", cv::FileStorage::READ);

	// Read in camera extrinsives and intrinsics.
	if (fs.isOpened())
	{
		// Read in camera matrix and distortion from output calibrated camera.
		fs["camera_matrix"] >> camera_matrix;
		//fs["square_size"] >> squareSize;
		//fs["image_points"] >> imagePoints;
		//fs["grid_points"] >> gridPoints;
		//fs["distortion_coefficients"] >> distortionCoefficients;
	}

    if (image.empty())                      
    {
        std::cout << "Could not open or find the image" << std::endl;
    }
	else
	{	
		cv::drawChessboardCorners(image, cv::Size2f(9, 7), gridPoints, true);

		cv::rectangle(image, cv::Rect(0, 0, 50, 50), cv::Scalar(0, 255, 128));
		imshow("Display Window", image);
	}

	cv::waitKey(0);
	*/
	return 0;
}