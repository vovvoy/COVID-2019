//#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>

using namespace cv;
using namespace std;

Mat frame, game_frame, bla, enemy;
double v_x = 1, v_y = 0, X, Y;
double speed = 3.0;
////////////////////////////  comeing soon....  ////////////////////
//double enemy_dif = 5;
//vector<pair<int, int>> enemies;

time_t seconds = std::time(nullptr);

void DrawImage(int x, int y){
	int enemy_row = enemy.rows;
	int enemy_col = enemy.cols;
	for (int i = 0; i < enemy_row; i++){
		int k = 0;
		for (int j = 0; j < enemy_col * 3; j+=3, k++){
			if (enemy.at<uchar>(i, j) < 100)
			game_frame.at<uchar>(i + x, k + y) = 255;
		}
	}
}

int main(int argc, char* argv[])
{
	VideoCapture cap;
	cap.open("Black_hall1.mp4");
	enemy = imread("virus.png");
	int frame_count = 0;
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video camera" << endl;
		return -1;
	}
	int key;
	game_frame = cv::Mat::zeros(1080,1920, CV_8U);
	X = game_frame.cols - 1;
	Y = game_frame.rows - 1;
	while (true)
	{
		game_frame = cv::Mat::zeros(1080,1920, CV_8U);
		cap >> frame;
		if (frame.empty()){
			cap.set(CAP_PROP_POS_AVI_RATIO, 0.0);
			continue ;
		}

		if (frame.empty())
		{
			cout << "Video camera is disconnected" << endl;
			break;
		}
		DrawImage(0, 0);
		cv::pyrDown(frame, frame);
//		cv::pyrDown(frame, frame);
		int n = 0, m;
		for (int i = game_frame.rows / 2 - frame.rows / 2; i <= game_frame.rows / 2 + frame.rows / 2 - 4; i++, n++){
			m = 0;
			for (int j = game_frame.cols / 2 - frame.cols / 2; j <= game_frame.cols / 2 + frame.cols / 2; j++, m += 3){
				if (frame.at<uchar>(n, m) > 80)
					game_frame.at<uchar>(i, j) = frame.at<uchar>(n, m);
			}
		}
		if (X + v_x * speed + enemy.cols / 2 < game_frame.cols && X + v_x * speed + enemy.cols / 2 > enemy.cols / 2 &&
		Y + v_y * speed + enemy.rows / 2 < game_frame.rows && Y + v_y * speed + enemy.rows / 2 > enemy.rows / 2) {
			DrawImage(X + v_x * speed, Y + v_y * speed);
			//			DeleteImage(X, Y);
			X = X + v_x * speed;
			Y = Y + v_y * speed;
		} else {
			double oldX = v_x;
			//			DeleteImage(X, Y);
			double angle = std::rand() % 360;
			v_x = v_x * cos(angle) - v_y * sin(angle);
			v_y = oldX * sin(angle) + v_y * cos(angle);
			X = game_frame.cols / 2;
			Y = game_frame.rows / 2;
		}
		imshow("window_name", game_frame);
		key = waitKey(10);
		if (key == 27)
			break;
	}
	return 0;

}


























