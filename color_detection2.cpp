#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <iostream>


int main()
{
	int num_frames = 0;
	time_t start, end;

	cv::VideoCapture cap("black_hall.mp4");
	const char* windowName = "Edges";
	cv::namedWindow(windowName);
	cv::Mat frame
	if (!cap.isOpened())  // if not success, exit program
		{
		std::cout << "Cannot open the web cam" << std::endl;
		return -1;
		}
	cap.set(cv::CAP_PROP_FPS, 30 );
	time(&start);
	VideoWriter writer;
	int codec = VideoWriter::fourcc('M', 'P', '4', 'V');
	std::string filename = "black_hall1.mp4";
	double fps = 15.0;
	writer.open(filename, codec, fps, sizeFrame, isColor);
	for (;;)
	{
		num_frames++;
		cap >> frame;
		cv::imshow(windowName, frame);
		if (cv::waitKey(30) >= 0) break;
	}
	time(&end);
	double seconds = difftime(end, start);
	std::cout << "FRAME NUMBER -> " << num_frames << std::endl << "SECONDS -> " << seconds << std::endl << "FRAME RATE -> " << num_frames / seconds << std::endl;
	return 0;
}