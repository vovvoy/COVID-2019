#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
#include <time.h>

using namespace cv;
using namespace std;

Mat frame, game_frame, bla, enemy, knife;
double v_x = 1, v_y = 0, X, Y;
double speed = 3.0;
int num_frames = 0;
VideoCapture teleport;
time_t seconds = std::time(nullptr);

void DrawImage(int x, int y){
	for (int i = 0, n = -(knife.rows / 2); i < knife.rows; i++, n++)
		for (int j = 0, m = -(knife.cols / 2); j < knife.cols * 3; j+=3, m++)
			if (knife.at<uchar>(i, j) < 100)
				game_frame.at<uchar>(n + x, m + y) = 255;
}

void DrawTeleport(){
	for (int n = 0, i = game_frame.rows / 2 - frame.rows / 2; i <= game_frame.rows / 2 + frame.rows / 2; i++, n++)
		for (int m = 0, j = game_frame.cols / 2 - frame.cols / 2; j <= game_frame.cols / 2 + frame.cols / 2; j++, m += 3)
			if (frame.at<uchar>(n, m) > 80)
				game_frame.at<uchar>(i, j) = frame.at<uchar>(n, m);
}

void DrawVirus(int x, int y){
	for (int i = 0, n = -(enemy.rows / 2); i < enemy.rows; i++, n++)
		for (int j = 0, m = -(enemy.cols / 2); j < enemy.cols * 3; j+=3, m++)
			if (enemy.at<uchar>(i, j) < 100)
				game_frame.at<uchar>(n + x, m + y) = 255;
}
void FindKnife(int *mid_i, int *mid_j, Mat mask){
	int max_i = -1, max_j = -1, min_i = 1000000, min_j = 1000000;

	for (int i = 0; i < mask.rows; i++){
		for (int j = 0; j < mask.cols; j++){
			if (mask.at<uchar>(i, j) == 255) {
					max_i = max(max_i, i);
					max_j = max(max_j, j);
					min_i = min(min_i, i);
					min_j = min(min_j, j);
			}
		}
	}
	*mid_i = (min_i + max_i) / 2;
	*mid_j = (min_j + max_j) / 2;
}

void MoveVirus(){
	if (X + v_x * speed + enemy.rows / 2 < game_frame.rows &&
	X + v_x * speed + enemy.rows / 2 > enemy.rows &&
	Y + v_y * speed + enemy.cols / 2 < game_frame.cols &&
	Y + v_y * speed + enemy.cols / 2 > enemy.cols) {
		DrawVirus(X + v_x * speed, Y + v_y * speed);
		X = X + v_x * speed;
		Y = Y + v_y * speed;
	} else {
		double oldX = v_x;
		double angle = std::rand() % 360;
		v_x = v_x * cos(angle) - v_y * sin(angle);
		v_y = oldX * sin(angle) + v_y * cos(angle);
		Y = game_frame.cols / 2 - 1;
		X = game_frame.rows / 2 - 1;
	}
}

void DrawLine(pair<int, int> A, pair<int, int> B){
	double a = abs(A.second - B.second);
	double b = abs(A.first - B.first);
	double c = sqrt(pow(A.first * B.first, 2) + pow(A.second * B.second, 2));
	double cos_angle = b / c;
	double sin_angle = a / c;
	double x = 1;
	double y = 0;
	x = cos_angle;
	y = sin_angle;
	for (int i = 0; i < 200; i++){
		game_frame.at<uchar>(A.first, A.second) = 255;
		A.first = A.first + x;
		A.second = A.second + Y;
	}
}

int main(int argc, char* argv[])
{
	int minH = 7, maxH = 32, minS = 246, maxS = 255, minV = 200, maxV = 255;
	std::vector<std::pair<int, int> >  line;
	cv::VideoCapture cap(0);
	cap.set(cv::CAP_PROP_FPS, 30);
	time_t start, end;
	teleport.open("Black_hall1.mp4");
	enemy = imread("virus_new.png");
	knife = imread("knife_new.jpg");
	game_frame = cv::Mat::zeros(720,1280, CV_8U);
	Y = game_frame.cols / 2 - 1;
	X = game_frame.rows / 2 - 1;
	time(&start);
	while (true)
	{
		Mat hsv, mask;

		num_frames++;
		game_frame = cv::Mat::zeros(720,1280, CV_8U);
		teleport >> frame;
		cap >> bla;
		flip(bla, bla, 1);
		cv::cvtColor(bla, hsv, COLOR_BGR2HSV);
		cv::inRange(hsv, cv::Scalar(minH, minS, minV), cv::Scalar(maxH, maxS, maxV), mask);

		int mid_i, mid_j;
		FindKnife(&mid_i, &mid_j, mask);
		if (mid_i < game_frame.rows && mid_j < game_frame.cols) {
			DrawImage(mid_i * 2, mid_j * 2);
		}

		if (frame.empty()){
			teleport.set(CAP_PROP_POS_AVI_RATIO, 0.0);
			continue ;
		}

		if (std::time(nullptr) - seconds == 10) {
			speed += 1;
			seconds = std::time(nullptr);
		}

		if (frame.empty())
		{
			cout << "Video camera is disconnected" << endl;
			break;
		}
		cv::pyrDown(frame, frame);
		cv::pyrDown(frame, frame);
//		cv::pyrDown(enemy, enemy);
		DrawTeleport();
		MoveVirus();
		imshow("window_name", game_frame);
		int key = waitKey(10);
		if (key == 27)
			break;
	}
	time(&end);
	double seconds = difftime(end, start);
	std::cout << "FRAME NUMBER -> " << num_frames << std::endl << "SECONDS -> " << seconds << std::endl << "FRAME RATE -> " << num_frames / seconds << std::endl;
	return 0;
}
