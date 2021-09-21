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
	void Teleport(cv::Mat game);
	void DrawEnemy(const cv::Mat &game, double &x, double &y);
	void DrawHP(const cv::Mat &game, double x, double y, int hp);
	void EnemyHP(cv::Mat &frame, std::pair<double, double> knife_,
				 std::pair<double, double> oldKnife_);
	void IterateEnemies(const cv::Mat &game, const cv::Mat &digits, std::pair<double, double> oldKnife_,
						std::pair<double, double> knife_, int &score, bool &isGameEnded);
	void Thread(cv::Mat frame);
	void ChangeScore(const cv::Mat &game, const cv::Mat &digits, int &score, bool flag);
	time_t & GetTime();
	void ClearEnemies();
	~Enemy();
	void FindEnemy(const cv::Mat &game, int start, int end);
private:
	void DirectEnemy(std::pair<double, std::pair<double, double>> &enemy, double &x, double &y, int &score);
	void MoveEnemy(std::pair<double, std::pair<double, double>> &enemy, double &x, double &y, int &score);
	std::vector<std::pair<double, std::pair<double, double>>> enemies_;
	cv::Mat enemy_;
	cv::Mat enemyMask_;
	cv::VideoCapture cap_;
	double speed_;
	time_t time_;

};


#endif //OPENCV_PROJECT_ENEMY_HPP
