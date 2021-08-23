#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>

using namespace cv;

using namespace std;
Mat frame, game_frame, bla, enemyImage, knifeImage, hsv, mask;
pair<double, double> enemy, /*knife,*/ enemyDir(1.0, 0.0), prev_knife;
double speed = 1.0;
int num_frames = 0, hp = 100;
typedef struct s_enemy{
	int x;
	int y;
	int angle;
	double vecX;
	double vecY;
	int speed;
	int hp;
} t_enemy;
int m = 0;
vector<t_enemy> enemies;
bool virus_flag = false;
VideoCapture teleport;
time_t seconds = std::time(nullptr);

time_t enemyBurn = std::time(nullptr);

void DrawKnife(int x, int y){
	for (int i = 0, n = -(knifeImage.rows / 2); i < knifeImage.rows; i++, n++)
		for (int j = 0, m = -(knifeImage.cols / 2); j < knifeImage.cols * 3; j+=3, m++)
			if (game_frame.at<uchar>(n + x, m + y) == 0)
				game_frame.at<uchar>(n + x, m + y) = knifeImage.at<uchar>(i, j);
}

void DrawTeleport(){
	for (int n = 0, i = game_frame.rows / 2 - frame.rows / 2; i <= game_frame.rows / 2 + frame.rows / 2; i++, n++)
		for (int m = 0, j = game_frame.cols / 2 - frame.cols / 2; j <= game_frame.cols / 2 + frame.cols / 2; j++, m += 3)
			if (frame.at<uchar>(n, m) > 80 && game_frame.at<uchar>(i, j) == 0)
				game_frame.at<uchar>(i, j) = frame.at<uchar>(n, m);
}
void DrawVirus(int x, int y){
	for (int i = 0, n = -(enemyImage.rows / 2); i < enemyImage.rows; i++, n++)
		for (int j = 0, m = -(enemyImage.cols / 2); j < enemyImage.cols * 3; j+=3, m++)
			game_frame.at<uchar>(n + x, m + y) = enemyImage.at<uchar>(i, j);
//	circle(game_frame, Point(y, x), 29, Scalar(230, 0, 126), 1, cv::LINE_AA);
	virus_flag = true;
}

pair<double, double> FindKnife(Mat mask){
	int max_i = -1, max_j = -1, min_i = 1000000, min_j = 1000000;

	for (int i = 0; i < mask.rows; i++)
		for (int j = 0; j < mask.cols; j++)
			if (mask.at<uchar>(i, j) == 255) {
					max_i = max(max_i, i);
					max_j = max(max_j, j);
					min_i = min(min_i, i);
					min_j = min(min_j, j);
			}
	if (max_i == -1)
		return make_pair(-1, -1);
	return make_pair((min_i + max_i) / 2, (min_j + max_j) / 2);
}

void MoveVirus(){
	for (auto enem = enemies.begin(); enem < enemies.end(); enem++)
		if ((enem->x + enem->vecX * enem->speed + (double)enemyImage.rows / 2 < game_frame.rows &&
			enem->x + enem->vecX * enem->speed + (double)enemyImage.rows / 2 > enemyImage.rows &&
			enem->y + enem->vecY * enem->speed + (double)enemyImage.cols / 2 < game_frame.cols &&
			enem->y + enem->vecY * enem->speed + (double)enemyImage.cols / 2 > enemyImage.cols) && enem->hp > 0) {
			DrawVirus(enem->x + enem->vecX * speed, enem->y + enem->vecY * enem->speed);
			enem->x += enem->vecX * enem->speed;
			enem->y += enem->vecY * enem->speed;
		} else {
			enemies.erase(enem);
		}
}

int main(int argc, char* argv[])
{
	pair<double, double> knife, oldKnife;
	int minH = 7, maxH = 32, minS = 246, maxS = 255, minV = 200, maxV = 255;
	std::vector<std::pair<int, int> >  line;
	cv::VideoCapture cap(0);
	cap.set(cv::CAP_PROP_FPS, 30);
	time_t start, end;
	teleport.open("Black_hall1.mp4");
	enemyImage = imread("virus_new1.png");
	knifeImage = imread("knife_new1.jpg");

	game_frame = cv::Mat::zeros(720,1280, CV_8U);
	enemy.second = (double)game_frame.cols / 2;
	enemy.first = (double)game_frame.rows / 2;
	srand((unsigned) time(nullptr));
	time(&start);
	while (true)
	{
		num_frames++;
		game_frame = cv::Mat::zeros(720,1280, CV_8U);
		teleport >> frame;
		cap >> bla;
		flip(bla, bla, 1);
		cv::cvtColor(bla, hsv, COLOR_BGR2HSV);
		cv::inRange(hsv, cv::Scalar(minH, minS, minV),
					cv::Scalar(maxH, maxS, maxV), mask);


		if (frame.empty()){
			teleport.set(CAP_PROP_POS_AVI_RATIO, 0.0);
			continue ;
		}
		cv::pyrDown(frame, frame);
		cv::pyrDown(frame, frame);

		if (std::time(nullptr) - seconds == 10) {
			speed += 1;
			seconds = std::time(nullptr);
		}
		if (std::time(nullptr) - enemyBurn == 1){
			t_enemy enemy;
			enemy.x = game_frame.rows / 2;
			enemy.y = game_frame.cols / 2;
			enemy.vecX = 1;
			enemy.vecY = 0;
			enemy.speed = 2;
			enemy.angle = rand() % 360;
			double oldX = enemy.vecX;
			enemy.vecX = enemy.vecX * cos(enemy.angle) - enemy.vecY * sin(enemy.angle);
			enemy.vecY = oldX * sin(enemy.angle) + enemy.vecY * cos(enemy.angle);
			enemy.hp = 100;
			enemies.push_back(enemy);
			enemyBurn = std::time(nullptr);
		}

		if (frame.empty())
		{
			cout << "Video camera is disconnected" << endl;
			break;
		}


		MoveVirus();
		oldKnife = knife;
		knife = FindKnife(mask);
		if (knife.first * 2 + (double)knifeImage.rows / 2 < game_frame.rows && knife.first * 2 - (double)knifeImage.rows / 2 >= 0 &&
			knife.second * 2 + (double)knifeImage.cols / 2 < game_frame.cols && knife.second * 2 - (double)knifeImage.cols / 2 >= 0) {
			DrawKnife((int) (knife.first * 2), (int) (knife.second * 2));
		}
		DrawTeleport();
		for (auto enem = enemies.begin(); enem < enemies.end(); enem++)
			if (sqrt(pow(enem->y - knife.second * 2 + (double)knifeImage.cols / 2, 2) + pow(enem->x - knife.first * 2 - (double)knifeImage.rows / 2, 2)) < 30) {
				if (sqrt(pow(enem->y - oldKnife.second * 2 + (double)knifeImage.cols / 2, 2) + pow(enem->x - oldKnife.first * 2 - (double)knifeImage.rows / 2, 2)) > 30){
					enem->hp -= 100;
//					cout <<  << hp << endl;
				}
			}
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
