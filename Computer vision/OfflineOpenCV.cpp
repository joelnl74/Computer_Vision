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

			// Draw the found corners on the image.
			cv::drawChessboardCorners(img, boardSize, corners, succes);

			// Show the image on the scsreen.
			cv::imshow("img", img);

			cv::waitKey(500);
	
			cv::destroyAllWindows();
		}
	}
}

void OfflineOpenCV::GetWorldSpaceCoords()
{
	// Get the known positions on the images and save those.
	for (int i = 0; i < boardSize.x; i++)
	{
		for (int j = 0; j < boardSize.y; j++)
		{
			std::vector<cv::Point3f> point;
			m_imagePoints.push_back(cv::Point3f(i * SquareSize, j * SquareSize, 0));
		}
	}
}

void OfflineOpenCV::CalibrateCamera()
{
	GetChessBoardCorners("images/", 5);
	GetWorldSpaceCoords();

	cv::calibrateCamera(m_imagePoints, m_objectPoints, cv::Point2f(0.025, 0.025), m_cameraMatrix, distcoefs, rvecs, tvecs);
}
