#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>

static const float SquareSize = 0.025;
static const cv::Point2i boardSize = cv::Point2i(9 , 6);

class OpenCV1
{
public:
	void GetChessBoardCorners(const std::string& imagePath, const int amount);
	void GetWorldSpaceCoords();
	void CalibrateCamera(const int amount, const std::string& imagePath, bool read);
	void SaveInformationToFile();
	void ReadInformationFromFile();
	std::vector<cv::Point2f> GetAxesPoints(const int imageIndex);

	cv::Point2f GetFirstCorner(const int imageIndex);
private:
	std::vector<std::vector<cv::Point3f>>  m_objectPoints;
	std::vector<std::vector<cv::Point2f>> m_imagePoints;
	
	cv::Mat m_cameraMatrix;
	cv::Mat distcoefs;
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
};

