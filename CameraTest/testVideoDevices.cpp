// #include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

int main()
{
	bool noValidChannels = true;
	std::cout << "Beginning scan for valid video channels..." << std::endl;

	for(int i = 0; i < 10; i++)
	{
		cv::VideoCapture video(i);

		if(video.isOpened())
		{
			std::cout << "Valid capture device found at input number " << i << std::endl;

			noValidChannels = false;
		}
	}

	if(noValidChannels)
	{
		std::cout << "No valid video channels found" << std::endl;
	}

	return(0);
}
