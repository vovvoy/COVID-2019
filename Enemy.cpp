#include "Enemy.hpp"

Enemy::Enemy(std::string path, int x, int y, double speed, int angle, int hp) {
	x_ = x;
	y_ = y;
	speed_ = speed;
	vecX_ = 1 * cos(angle);
	vecY_ = 1 * sin(angle);
	hp_ = hp;
	enemyImage_ = cv::imread(path);
}

void Enemy::DrawEnemy(cv::Mat game_frame) {
	for (int i = 0; i < (double)enemyImage_.rows  * (double)hp_ / 100; i++)
		for (int j = 0; j < 4; j++)
			game_frame.at<uchar>(x_ + j + -(enemyImage_.cols / 2) - 10, i + y_ + -(enemyImage_.rows / 2)) = 255;

	for (int i = 0, n = -(enemyImage_.rows / 2); i < enemyImage_.rows; i++, n++)
		for (int j = 0, m = -(enemyImage_.cols / 2); j < enemyImage_.cols * 3; j+=3, m++)
			if (enemyImage_.at<uchar>(i, j) > 100)
				game_frame.at<uchar>(n + x_,m + y_) = enemyImage_.at<uchar>(i, j);
}

Enemy::~Enemy(){ }