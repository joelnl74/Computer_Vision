#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>

static const float SquareSize = 0.025;
static const cv::Point2i boardSize = cv::Point2i(9 , 6);

class OfflineOpenCV
{
public:
	void GetChessBoardCorners(const std::string& imagePath, const int amount);
	void GetWorldSpaceCoords();
	void CalibrateCamera();
private:
	std::vector<std::vector<cv::Point3f>>  m_imagePoints;
	std::vector<std::vector<cv::Point2f>> m_objectPoints;
	
	cv::Mat m_cameraMatrix;
	cv::Mat distcoefs;
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
};

