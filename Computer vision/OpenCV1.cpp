#include "OpenCV1.h"

void OpenCV1::GetChessBoardCorners(const std::string& imagePath, const int amount)
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

void OpenCV1::GetWorldSpaceCoords()
{
	// Vector of known points in this image.
	std::vector<cv::Point3f> points;

	// Get the known positions on the images and save those.
	for (int i = 0; i < boardSize.y; i++)
	{
		for (int j = 0; j < boardSize.x; j++)
		{
			points.push_back(cv::Point3f(j, i, 0));
		}
	}

	m_objectPoints.push_back(points);
}

void OpenCV1::CalibrateCamera(const int amount, const std::string &imagePath, bool read)
{
	if (read)
	{
		ReadInformationFromFile();

		return;
	}

	GetChessBoardCorners(imagePath, amount);

	// Needed to get the image size.
	cv::Mat img = cv::imread("images/0.jpg");

	// Calibrate the camera, let opencv generate the camera matrix and distortion coefs.
	cv::calibrateCamera(m_objectPoints, m_imagePoints, img.size(), m_cameraMatrix, distcoefs, rvecs, tvecs);

	SaveInformationToFile();
}

void OpenCV1::SaveInformationToFile()
{
	cv::FileStorage fs;

	fs.open("CalibrationData.xml", cv::FileStorage::WRITE);

	if (fs.isOpened())
	{
		fs << "camera_matrix" << m_cameraMatrix;
		fs << "object_points" << m_objectPoints;
		fs << "image_points" << m_imagePoints;
		fs << "rotation_vectors" << rvecs;
		fs << "translation_vector" << tvecs;
		fs << "dist_coefs" << distcoefs;
	}
}

void OpenCV1::ReadInformationFromFile()
{
	cv::FileStorage fs;

	fs.open("CalibrationData.xml", cv::FileStorage::READ);

	if (fs.isOpened())
	{
		fs["camera_matrix"] >> m_cameraMatrix;
		fs["object_points"] >> m_objectPoints;
		fs["image_points"] >> m_imagePoints;
		fs["rotation_vectors"] >> rvecs;
		fs["translation_vector"] >> tvecs;
		fs["dist_coefs"] >> distcoefs;
	}
}

cv::Point2f OpenCV1::GetFirstCorner(const int imageIndex)
{
	return m_imagePoints[imageIndex][0];
}

std::vector<cv::Point2f> OpenCV1::GetAxesPoints(const int imageIndex)
{
	std::vector <cv::Point3f> axis;
	axis.push_back(cv::Point3f(3, 0, 0));
	axis.push_back(cv::Point3f(0, 3, 0));
	axis.push_back(cv::Point3f(0, 0, -3));

	axis.push_back(cv::Point3f(0, 0, 0));
	axis.push_back(cv::Point3f(1, 0, 0));
	axis.push_back(cv::Point3f(0, 1, 0));
	axis.push_back(cv::Point3f(0, 0, -1));

	axis.push_back(cv::Point3f(1, 1, 0));
	axis.push_back(cv::Point3f(1, 0, -1));
	axis.push_back(cv::Point3f(0, 1, -1));
	axis.push_back(cv::Point3f(1, 1, -1));

	std::vector <cv::Point2f> imagePoints;
	cv::Mat local_rvecs;
	cv::Mat local_tvecs;

	cv::solvePnP(m_objectPoints[imageIndex], m_imagePoints[imageIndex], m_cameraMatrix, distcoefs, local_rvecs, local_tvecs);
	cv::projectPoints(axis, local_rvecs, local_tvecs, m_cameraMatrix, distcoefs, imagePoints);

	return imagePoints;
}
