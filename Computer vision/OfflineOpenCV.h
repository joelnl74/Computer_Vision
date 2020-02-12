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
	std::vector<cv::Vec3f>  m_imagePoints;
	std::vector<std::vector<cv::Point2f>> m_objectPoints;
	std::vector<std::vector<cv::Point2f>> m_markerCorners, rejected;
	
	cv::Mat m_cameraMatrix;
	cv::Mat ret;
	cv::Mat mtx;
	cv::Mat distcoefs; 
	cv::Mat rvecs; 
	cv::Mat tvecs;
};

