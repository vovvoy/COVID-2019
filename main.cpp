#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main( int argc, char** argv ) {
	cv::Mat enemy = cv::imread("knife.jpg", IMREAD_ANYDEPTH);
//	for (int i = 0; i < enemy.rows; i++){
//		for (int j = 0; j < enemy.cols; j++){
//			if (enemy.at<uchar>(i, j) < 100)
//				frame.at<uchar>(i + frame.rows / 2 - enemy.rows / 2, j + frame.cols / 2 - enemy.cols / 2) = 255;
//		}
//	}
	cv::pyrDown(enemy, enemy);
	cv::pyrDown(enemy, enemy);
	cv::pyrDown(enemy, enemy);
	cv::pyrDown(enemy, enemy);
//	cv::imshow("bla", enemy);
//	waitKey();
	cv::imwrite("knife_new.jpg", enemy);
	return 0;
}
