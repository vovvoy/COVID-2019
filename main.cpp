#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main( int argc, char** argv ) {
	cv::Mat enemy = cv::imread("virus1.png", IMREAD_ANYDEPTH);

	for (int i = 0; i < enemy.rows; i++){
		for (int j = 0; j < enemy.cols; j++){
			if (enemy.at<uchar>(i, j) < 100) {
				enemy.at<uchar>(i, j) = 255;
			}
			else {
				enemy.at<uchar>(i, j) = 0;
			}
		}
	}

	cv::pyrDown(enemy, enemy);
	cv::pyrDown(enemy, enemy);
	cv::pyrDown(enemy, enemy);
	cv::pyrDown(enemy, enemy);
//	cv::imshow("bla", enemy);
//	waitKey();
	cv::imwrite("virus_new1.png", enemy);
	return 0;
}
