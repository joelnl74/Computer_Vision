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
		std::vector<cv::Point2f> corners;

		// Find chess board corners(each cell on the checkerboard).
		bool succes = cv::findChessboardCorners(img, boardSize, corners);

		if (succes)
		{
			// Save the points found on the checkerboard.
			m_objectPoints.push_back(corners);
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

	m_imagePoints.push_back(points);
}

void OfflineOpenCV::CalibrateCamera()
{
	GetChessBoardCorners("images/", 12);

	// Needed to get the image size.
	cv::Mat img = cv::imread("images/0.jpg");

	// Calibrate the camera, let opencv generate the camera matrix and distortion coefs.
	cv::calibrateCamera(m_imagePoints, m_objectPoints, img.size(), m_cameraMatrix, distcoefs, rvecs, tvecs);
}

cv::Point2f OfflineOpenCV::GetFirstCorner()
{
	return m_objectPoints[0][0];
}

void OfflineOpenCV::DrawFrameAxes(cv::Mat image)
{
	cv::drawFrameAxes(image, m_cameraMatrix, distcoefs, rvecs[0], tvecs[0], 1);
}
