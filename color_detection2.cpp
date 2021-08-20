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
	cap.set(cv::CAP_PROP_FPS, 30 );
	time(&start);
	cv::Mat img,cimg;
	for (;;)
	{
		num_frames++;
		cap >> frame;
		cv::flip(frame, frame, 1);
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		GaussianBlur(gray, gray, cv::Size(5, 5), 0, 0);
		cv::medianBlur(gray, img, 5);
		cv::cvtColor(img, cimg, cv::COLOR_GRAY2BGR);
		cv::adaptiveThreshold(img, img, 255,cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 3.5);
		cv::erode(img, img, getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
		cv::dilate(img, img, getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
		cv::imshow("cimg", img);
		std::vector<cv::Vec3f> circles;
		cv::HoughCircles(img, circles, cv::HOUGH_GRADIENT, 1,
						 img.rows / 16,
						 100, 30, 0, 30
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
		cv::imshow(windowName, frame);
		if (cv::waitKey(30) >= 0) break;
	}
	time(&end);
	double seconds = difftime(end, start);
	std::cout << "FRAME NUMBER -> " << num_frames << std::endl << "SECONDS -> " << seconds << std::endl << "FRAME RATE -> " << num_frames / seconds << std::endl;
	return 0;
}