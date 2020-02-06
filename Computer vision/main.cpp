#include<opencv2/opencv.hpp>
#include<iostream>

int main()
{
	cv::Mat image = cv::imread("jpg-vs-jpeg.jpg");

    if (image.empty())                      
    {
        std::cout << "Could not open or find the image" << std::endl;
    }
	else
	{
		cv::rectangle(image, cv::Rect(0, 0, 100, 100), cv::Scalar(0, 255, 128));
		imshow("Display Window", image);
	}

	cv::waitKey(0);

	return 0;
}