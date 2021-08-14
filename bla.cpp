#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>

using namespace cv;
using namespace std;

Mat frame, game_frame, bla;
double v_x = 1, v_y = 0, X, Y;
double speed = 3.0;
////////////////////////////comeing soon....////////////////////
//double enemy_dif = 5;
//vector<pair<int, int>> enemies;

time_t seconds = std::time(nullptr);

void DrawImage(int x, int y){
	game_frame.at<uchar>(y - 1, x - 1) = 100;
	game_frame.at<uchar>(y - 1, x) = 100;
	game_frame.at<uchar>(y - 1, x + 1) = 100;
	game_frame.at<uchar>(y, x - 1) = 100;
	game_frame.at<uchar>(y, x) = 100;
	game_frame.at<uchar>(y, x + 1) = 100;
	game_frame.at<uchar>(y + 1, x - 1) = 100;
	game_frame.at<uchar>(y + 1, x) = 100;
	game_frame.at<uchar>(y + 1, x + 1) = 100;

}

void DeleteImage(int x, int y){
	game_frame.at<uchar>(y - 1, x - 1) = 24;
	game_frame.at<uchar>(y - 1, x) = 24;
	game_frame.at<uchar>(y - 1, x + 1) = 24;
	game_frame.at<uchar>(y, x - 1) = 24;
	game_frame.at<uchar>(y, x) = 24;
	game_frame.at<uchar>(y, x + 1) = 24;
	game_frame.at<uchar>(y + 1, x - 1) = 24;
	game_frame.at<uchar>(y + 1, x) = 25;
	game_frame.at<uchar>(y + 1, x + 1) = 24;
}

int main(int argc, char* argv[])
{
	VideoCapture cap;

	cap.open("Black_hall1.mp4");
	int frame_count = 0;
	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
	string window_name = "My Camera Feed";
	int key;
	game_frame = cv::Mat::zeros(1080,1920, CV_8U);
	X = game_frame.cols - 1;
	Y = game_frame.rows - 1;
//	cout << X << " " << Y << endl;
	for (int i = 0; i < game_frame.rows; i++){
		for (int j = 0; j < game_frame.cols; j++){
			if (j % 3 == 0)
				game_frame.at<uchar>(i, j) = 21;
			else if (j % 3 == 1)
				game_frame.at<uchar>(i, j) = 24;
			else
				game_frame.at<uchar>(i, j) = 27;
		}
	}
	cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
	namedWindow(window_name); //create a window called "My Camera Feed"
	while (true)
	{
//		bla = imread("virus1.xpm", IMREAD_COLOR);
//		cv::cvtColor(bla, frame, COLOR_BGR2BGRA);
		if (std::time(nullptr) - seconds == 10) {
			speed += 1;
			seconds = std::time(nullptr);
		}
		cap >> frame;
		if (frame.empty()){
			cap.set(CAP_PROP_POS_AVI_RATIO, 0.0);
			continue ;
		}

		if (frame.empty())
		{
			cout << "Video camera is disconnected" << endl;
//			cin.get(); //Wait for any key press
			break;
		}

		cv::pyrDown(frame, frame);
		cv::pyrDown(frame, frame);
		int n = 0, m;
		for (int i = game_frame.rows / 2 - frame.rows / 2; i <= game_frame.rows / 2 + frame.rows / 2; i++, n++){
			m = 0;
			for (int j = game_frame.cols / 2 - frame.cols / 2; j <= game_frame.cols / 2 + frame.cols / 2; j++, m += 3){
				game_frame.at<uchar>(i, j) = frame.at<uchar>(n, m);
			}
		}
if (X + v_x * speed + 1 < game_frame.cols && X + v_x * speed + 1 > 2 &&
	Y + v_y * speed + 1 < game_frame.rows && Y + v_y * speed + 1 > 2) {
			DrawImage(X + v_x * speed, Y + v_y * speed);
			DeleteImage(X, Y);
			X = X + v_x * speed;
			Y = Y + v_y * speed;
		} else {
			double oldX = v_x;
			DeleteImage(X, Y);
			double angle = std::rand() % 360;
			v_x = v_x * cos(angle) - v_y * sin(angle);
			v_y = oldX * sin(angle) + v_y * cos(angle);
			X = game_frame.cols / 2;
			Y = game_frame.rows / 2;
		}
//		game_frame.copyTo(frame);
//		setMouseCallback(window_name, CallBackFunc, NULL);
		imshow(window_name, game_frame);
		key = waitKey(10);
		if (key == 27)
		{
			cout << "Esc key is pressed by user. Stoppig the video" << endl;
			break;
		}
	}
	return 0;

}