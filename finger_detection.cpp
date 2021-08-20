#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <iostream>


int main()
{
	int num_frames = 0;
	time_t start, end;

	cv::VideoCapture cap(0);
	const char* windowName = "Edges";
	cv::namedWindow(windowName);
	cv::Mat frame, edges, gray;
	if (!cap.isOpened())  // if not success, exit program
		{
			std::cout << "Cannot open the web cam" << std::endl;
			return -1;
		}
	std::cout << "FPS -> " << cap.set(cv::CAP_PROP_FPS, 30 ) << std::endl;
//	cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
//	cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
	time(&start);
	for (;;)
	{
		num_frames++;
		cap >> frame;
		cv::flip(frame, frame, 1);
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		GaussianBlur(gray, gray, cv::Size(5, 5), 1.5, 1.5);
		cv::medianBlur(gray, gray, 5);
		cv::adaptiveThreshold(gray, gray, 255,cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 3.5);
		cv::erode(gray, gray, getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
		cv::dilate(gray, gray, getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
//		Canny(edges, edges, 0, 30, 3);
		std::vector<cv::Vec3f> circles;
		cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1,
						 gray.rows / 16,
						 100, 30, 1, 30
						 );
		for (size_t i = 0; i < circles.size(); i++){
			cv::Vec3i c = circles[i];
			cv::Point center = cv::Point(c[0], c[1]);
			std::cout << c[0] << " " << c[1] << std::endl;
			cv::circle(frame, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
			int radius = c[2];
			cv::circle(frame, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
		}
//		gray += edges;
//		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		cv::imshow(windowName, gray);
		if (cv::waitKey(30) >= 0) break;
	}
	time(&end);
	double seconds = difftime(end, start);
	std::cout << "FRAME NUMBER -> " << num_frames << std::endl << "SECONDS -> " << seconds << std::endl << "FRAME RATE -> " << num_frames / seconds << std::endl;
	return 0;
}