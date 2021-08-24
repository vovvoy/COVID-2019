#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc.hpp>
#include <time.h>


using namespace std;
using namespace cv;
Mat frame;
void DrawKnife(int x, int y){
	for (int i = x - 1; i < x + 2; i++){
		for (int j = y - 1; j < y + 2; j++){
			frame.at<Vec3b>(i, j)[0] = 255;
			frame.at<Vec3b>(i, j)[1] = 255;
			frame.at<Vec3b>(i, j)[2] = 255;
		}
	}
}

int main()
{
	int num_frames = 0;
	time_t start, end;
	int max_i, max_j, min_i, min_j;
	cv::VideoCapture cap(0);
	cap.set(cv::CAP_PROP_FRAME_COUNT, 30);
	int minH = 7, maxH = 32, minS = 246, maxS = 255, minV = 200, maxV = 255;
	time(&start);
	float radius;
	while (1)
	{
		max_i = -1, max_j = -1, min_i = 1000000, min_j = 1000000;
		Mat mask, result;
		num_frames++;
		cap >> frame;
		flip(frame, frame, 1);
		cv::Mat hsv;
		cv::cvtColor(frame, hsv, COLOR_BGR2HSV);

		cv::inRange(hsv, cv::Scalar(minH, minS, minV), cv::Scalar(maxH, maxS, maxV), mask);
//		cv::bitwise_and(frame, frame, result, mask = mask);

		for (int i = 0; i < mask.rows; i++){
			for (int j = 0; j < mask.cols; j++){
				if (mask.at<uchar>(i, j) == 255) {
					if (max_i < i)
						max_i = i;
					if (max_j < j)
						max_j = j;
					if (min_i > i)
						min_i = i;
					if (min_j > j)
						min_j = j;
				}
			}
		}
		int mid_i = (min_i + max_i) / 2;
		int mid_j = (min_j + max_j) / 2;
		if (min_i < 1000000 && min_j < 1000000)
			DrawKnife(mid_i, mid_j);
		cv::imshow("frame", frame);
		if (cv::waitKey(30) >= 0) break;
	}
	time(&end);
	double seconds = difftime(end, start);
	std::cout << "FRAME NUMBER -> " << num_frames << std::endl << "SECONDS -> " << seconds << std::endl << "FRAME RATE -> " << num_frames / seconds << std::endl;
	return 0;
}