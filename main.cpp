#include "Game.hpp"
#include <cmath>
using namespace std;
using namespace cv;

time_t enemyBurn = std::time(nullptr);

std::map<std::string, std::string> images_name = {
		{"back_ground", "images/back_ground.jpg"},
		{"virus", "images/virus.png"},
		{"pills", "images/pills.png"},
		{"virus_mask", "images/virus_mask.png"},
		{"pills_mask", "images/pills_mask.png"},
 };

std::map<std::string, cv::Mat> images = {
		{"back_ground", imread(images_name["back_ground"])},
		{"virus", imread(images_name["virus"])},
		{"pills", imread(images_name["pills"])},
		{"virus_mask", imread(images_name["virus_mask"])},
		{"pills_mask", imread(images_name["pills_mask"])},
};

int main( int argc, char** argv ) {
	Game COVID_19;
	COVID_19.Run();
//	Mat frame, video;
//	VideoCapture cap("images/teleport1.mp4");
//	frame = imread("images/back_ground.jpg");
//
//	int cnt = 0;
//	srand((unsigned)time(nullptr));
//	while (true) {
//		if (std::time(nullptr) - enemyBurn >= 1){
//			while (true) {
//				cap >> video;
//				if (video.empty()){
//					cap.set(cv::CAP_PROP_POS_AVI_RATIO, 0.0);
//					break ;
//				}
//				for (int i = 0; i < video.cols; i++)
//					for (int j = 0; j < video.rows; j++) {
//						Vec3b black = video.at<Vec3b>(Point(i, j));
//						if (black[1] < 232 && black[2] < 232 && black[0] < 232) {
//							Vec3b &fr = frame.at<Vec3b>(frame.rows / 2 - video.rows / 2 + j,
//														frame.cols / 2 - video.cols / 2 + i);
//							fr[0] = black[0];
//							fr[1] = black[1];
//							fr[2] = black[2];
//						}
//					}
//				imshow("game", frame);
//				waitKey(1);
//			}
//			images["virus"].copyTo(frame(Rect(640 - 25, 360 - 25, images["virus"].cols, images["virus"].rows)), images["virus_mask"]);
//			enemyBurn = std::time(nullptr);
//		}
//
//
//		set<pair<double, double>> mp;
//
//		for (int x = 0; x < frame.cols - 50; x++) {
//			for (int y = 0; y < frame.rows - 50; y++) {
//				Vec3b back = frame.at<Vec3b>(Point(x, y));
//				Vec3b back1 = frame.at<Vec3b>(Point(x, y + 1));
//				Vec3b back2 = frame.at<Vec3b>(Point(x, y));
//				Vec3b back3 = frame.at<Vec3b>(Point(x, y + 1));
//				if (back[0] == 251 && back[1] == 158 && back[2] == 213 &&
//					back1[0] == 250 && back1[1] == 149 && back1[2] == 208) {
//					cnt++;
//					mp.insert(make_pair(x + 25, y - 2));
//				}
//				if (back3[0] == 251 && back3[1] == 154 && back3[2] == 210 &&
//					back2[0] == 250 && back2[1] == 145 && back2[2] == 208) {
//					cnt++;
//					mp.insert(make_pair(x - 24, y + 4));
//				}
//			}
//		}
//		double angle, x, y;
//		frame = images["back_ground"].clone();
//		for (const auto & it : mp) {
//			if (it.first == 640 && it.second == 360){
//				angle = rand() % 80;
//				x = it.first + cos(angle) * 4;
//				y = it.second + sin(angle) * 4;
//			} else {
//				double length = sqrt(pow(it.first - 640.0, 2) + pow(it.second - 360.0, 2));
//				double vx, vy;
//				vx = (it.first - 640.0) / length;
//				vy = (it.second - 360.0) / length;
//				x = it.first + vx * 4;
//				y = it.second + vy * 4;
//			}
//			if (x + 25 < frame.cols && x + 25 > 50 && y + 25 < frame.rows + 10 && y + 25 > 50)
//				images["virus"].copyTo(frame(Rect((int)x - 25, (int)y - 25, 50, 50)), images["virus_mask"]);
//		}
//
//		imshow("game", frame);
//		if (waitKey(10) == 27)
//			break ;
//	}
	return 0;
}

