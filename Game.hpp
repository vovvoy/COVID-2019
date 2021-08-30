#ifndef OPENCV_PROJECT_GAME_HPP
#define OPENCV_PROJECT_GAME_HPP

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
#include <map>
#include "Weapon.hpp"
#include "Enemy.hpp"

class Game {
public:
	Game(std::string black_hall, double speed, int hp);
	void DrawTeleport();
	void MoveEnemy();
	void WeaponDamage(int hp);
	int KeyCodes(int key);
	void Run();
	~Game();
	cv::VideoCapture teleport_;
	cv::Mat frame_, game_frame_;
	int num_frames_ = 0;
	double speed_;
	short score_ = 0;
	int minH = 7, maxH = 32, minS = 246, maxS = 255, minV = 200, maxV = 255;
	int hp_	;
	time_t enemyBurn_;
	bool isGameEnded_ = false;
	std::vector<Enemy> enemies_;
};


#endif //OPENCV_PROJECT_GAME_HPP
