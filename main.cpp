#include "Game.hpp"

using namespace std;
using namespace cv;

std::map<std::string, std::string> images = {
		{"back_ground", "images/back_ground.jpg"},
		{"virus", "images/virus.png"},
		{"pills", "images/pills.png"},
		{"virus_mask", "images/virus_mask.png"},
		{"pills_mask", "images/pills_mask.png"},
 };

int main( int argc, char** argv ) {
	Game Valhalla("black_hall.mp4", 2.0, 100);
	Valhalla.Run();
//	Mat backGround = imread("images/back_ground.jpg");
//	Mat virus = imread("images/virus.png");
//	Mat pills = imread("images/pills.png");
//	Mat virusMask = imread("images/virus_mask.png");
//	Mat pillsMask = imread("images/pills_mask.png");
//	Mat frame;
//	VideoCapture cap("black_hall.mp4");
//	virus.copyTo(backGround(Rect(10, 10, virus.cols, virus.rows)), virusMask);
//	pills.copyTo(backGround(Rect(500, 200, pills.cols, pills.rows)), pillsMask);
//	while (true){
//		cap >> frame;
//		cout << frame.channels() << endl;
//		if (frame.empty()){
//			cap.set(cv::CAP_PROP_POS_AVI_RATIO, 0.0);
//			continue ;
//		}
//		for (int i = 0, x = 400; i < frame.rows; i++, x++)
//			for (int j = 0, y = 400; j < frame.cols; j++, y++)
//				if (frame.at<uchar>(i, j) > 100)
//					backGround.at<uchar>(x, y) = frame. at<uchar>(i, j);
//		imshow("mask_inv", backGround);
//		int key = waitKey(10);
//		if (key == 27)
//			break ;
//	}

	return 0;
}
