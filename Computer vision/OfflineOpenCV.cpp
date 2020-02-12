#include "OfflineOpenCV.h"

void OfflineOpenCV::GetChessBoardCorners(const std::string& imagePath, const int amount)
{
	for (int i = 0; i < amount; i++)
	{
		std::string path = imagePath;
		path.append(std::to_string(i));
		path.append(".jpg");
		cv::Mat img = cv::imread(path);
		std::vector<cv::Point2f> corners;
		bool succes = cv::findChessboardCorners(img, boardSize, corners);

		if (succes)
		{
			m_objectPoints.push_back(corners);
			cv::drawChessboardCorners(img, boardSize, corners, succes);
			cv::imshow("img", img);

			cv::waitKey(500);
	
			cv::destroyAllWindows();
		}
	}
}

void OfflineOpenCV::GetWorldSpaceCoords()
{
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

	cv::calibrateCamera(m_objectPoints, m_imagePoints, cv::Point2f(0.025, 0.025), m_cameraMatrix, distcoefs, rvecs, tvecs);
}
