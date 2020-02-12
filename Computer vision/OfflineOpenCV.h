#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
class OfflineOpenCV
{
public:
	void CalibrateCamera(const std::string& imagePath, const int amount, cv::Point2i boardSize);
private:
	std::vector<cv::Point3f> m_imagePoints;
	std::vector<std::vector<cv::Point3f>> m_objectPoints;
};

