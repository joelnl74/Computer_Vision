#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>

static const float SquareSize = 0.025;
static const cv::Point2i boardSize = cv::Point2i(9 , 6);

class OpenCV1
{
public:
	// Calibrates the camera
	void GetChessBoardCorners(const std::string& imagePath, const int amount);
	// GETS THE KNOWN COORDINATES OF THE IMAGE
	void GetWorldSpaceCoords();
	// Entry point of the functions determines if the user wants to calibrate first or read in
	void CalibrateCamera(const int amount, const std::string& imagePath, bool read);
	// Write calibrated data to file.
	void SaveInformationToFile();
	// Read calibrated data from file
	void ReadInformationFromFile();

	// GETS THE PROJECTED POINTS OF THE IMAGE TO DRAW OUR 3D axis and cube
	std::vector<cv::Point2f> GetAxesPoints(const int imageIndex);
	// GETS THE ORIGIN OF THE CHESSBOARD POINT 0,0
	cv::Point2f GetFirstCorner(const int imageIndex);
private:
	// object points
	std::vector<std::vector<cv::Point3f>>  m_objectPoints;
	// image points
	std::vector<std::vector<cv::Point2f>> m_imagePoints;
	// camera matrix
	cv::Mat m_cameraMatrix;
	// distcoefs
	cv::Mat distcoefs;
	// rotation vectors
	std::vector<cv::Mat> rvecs;
	// translation vectors
	std::vector<cv::Mat> tvecs;
};

