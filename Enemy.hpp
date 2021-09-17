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
#include <thread>

class Enemy {
public:
	Enemy(cv::Mat &enemy, cv::Mat &enemy_mask, const std::string &teleport);
	void Teleport(cv::Mat & game);
	void DrawEnemy(const cv::Mat &game, double &x, double &y);
	void DrawHP(const cv::Mat &game, double x, double y, int hp);
	void FindEnemy(const cv::Mat& game);
	void Thread(cv::Mat frame, std::thread &t);
	void ChangeScore(const cv::Mat &game, const cv::Mat &digits, int &score, bool flag);
	void DirectEnemy(std::pair<double, std::pair<double, double>> &enemy, double &x, double &y);
	void IterateEnemies(const cv::Mat &game, const cv::Mat &digits, std::pair<double, double> oldKnife_,
						std::pair<double, double> knife_, int &score, bool &isGameEnded);
	void MoveEnemy(std::pair<double, std::pair<double, double>> &enemy, double &x, double &y);
	~Enemy();

	cv::Mat enemy_;
	cv::Mat enemyMask_;
	std::set<std::pair<double, std::pair<double, double>>> enemies_;
	cv::VideoCapture cap_;
	int x_;
	int y_;
	double vecX_;
	double vecY_;
	double speed_;
	int hp_;

};


#endif //OPENCV_PROJECT_ENEMY_HPP
