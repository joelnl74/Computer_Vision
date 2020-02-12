#include "OfflineOpenCV.h"

void OfflineOpenCV::CalibrateCamera(const std::string& imagePath, const int amount, cv::Point2i boardSize)
{
	for (int i = 0; i < amount; i++)
	{
		cv::Mat img = cv::imread(imagePath + std::to_string(i));
		std::vector<cv::Point3f> temp;
		bool succes = cv::findChessboardCorners(img, boardSize, temp);

		if (succes)
		{
			m_objectPoints.push_back(temp);

			cv::drawChessboardCorners(img, boardSize, temp, succes);
			cv::imshow("img", img);

			cv::waitKey(500);
	
			cv::destroyAllWindows();
		}
	}
}
