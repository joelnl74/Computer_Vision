#include "OfflineOpenCV.h"

void OfflineOpenCV::GetChessBoardCorners(const std::string& imagePath, const int amount)
{
	for (int i = 0; i < amount; i++)
	{
		// Create image path
		std::string path = imagePath;
		path.append(std::to_string(i));
		path.append(".jpg");

		// Read in images
		cv::Mat img = cv::imread(path);
		cv::Mat gray;
		cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
		std::vector<cv::Point2f> corners;

		// Find chess board corners(each cell on the checkerboard).
		bool succes = cv::findChessboardCorners(img, boardSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

		if (succes)
		{
			cv::cornerSubPix(gray, corners, boardSize, cv::Size(-1, -1), 
				cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.1));

			// Save the points found on the checkerboard.
			m_imagePoints.push_back(corners);
			GetWorldSpaceCoords();

			// Draw the found corners on the image.
			cv::drawChessboardCorners(img, boardSize, corners,cv::CALIB_CB_ADAPTIVE_THRESH |cv::CALIB_CB_FILTER_QUADS);

			// Show the image on the scsreen.
			cv::imshow("img", img);

			cv::waitKey(500);
	
			cv::destroyAllWindows();
		}
	}
}

void OfflineOpenCV::GetWorldSpaceCoords()
{
	// Vector of known points in this image.
	std::vector<cv::Point3f> points;

	// Get the known positions on the images and save those.
	for (int i = 0; i < boardSize.y; i++)
	{
		for (int j = 0; j < boardSize.x; j++)
		{
			points.push_back(cv::Point3f(j * SquareSize, i * SquareSize, 0));
		}
	}

	m_objectPoints.push_back(points);
}

void OfflineOpenCV::CalibrateCamera()
{
	GetChessBoardCorners("images/", 12);

	// Needed to get the image size.
	cv::Mat img = cv::imread("images/0.jpg");

	// Calibrate the camera, let opencv generate the camera matrix and distortion coefs.
	cv::calibrateCamera(m_objectPoints, m_imagePoints, img.size(), m_cameraMatrix, distcoefs, rvecs, tvecs);
}

cv::Point2f OfflineOpenCV::GetFirstCorner()
{
	return m_imagePoints[imageIndex][0];
}

std::vector<cv::Point2f> OfflineOpenCV::GetAxesPoints()
{
	std::vector <cv::Point3f> objectPoints;
	objectPoints.push_back(cv::Point3f(1, 0, 0));
	objectPoints.push_back(cv::Point3f(0, 1, 0));
	objectPoints.push_back(cv::Point3f(0, 0, 1));

	std::vector <cv::Point2f> imagePoints;

	cv::projectPoints(objectPoints, rvecs[imageIndex], tvecs[imageIndex], m_cameraMatrix, distcoefs, imagePoints);


	return imagePoints;
}
