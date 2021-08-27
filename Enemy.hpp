#ifndef OPENCV_PROJECT_ENEMY_HPP
#define OPENCV_PROJECT_ENEMY_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <ctime>

class Enemy {
public:
	Enemy(std::string path, int x, int y, double speed, int angle, int hp);
	void DrawEnemy(cv::Mat game_frame);
//	void MoveEnemy();
	~Enemy();

	cv::Mat enemyImage_;

	int x_;
	int y_;
	double vecX_;
	double vecY_;
	double speed_;
	int hp_;
};


#endif //OPENCV_PROJECT_ENEMY_HPP
