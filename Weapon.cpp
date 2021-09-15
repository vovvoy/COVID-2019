#include "Weapon.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <thread>

Weapon::Weapon(cv::Mat &pills, cv::Mat &pills_mask) {
//	this->cap_.open(0);
	pills_ = pills;
	pillsMask_ = pills_mask;
}



void Weapon::MoveWeapon(cv::Mat game) {
	if (knife_.first + 25 < game.cols - 10 && knife_.first + 25 > 50 && knife_.second + 25 < game.rows && knife_.second + 25 > 50) {
		pills_.copyTo(game(cv::Rect(knife_.first - 25, knife_.second - 25, pills_.cols, pills_.rows)), pillsMask_);
	}
}


void Weapon::DrawWeapon(int x, int y, cv::Mat &game_frame) {
	for (int i = 0, n = -(pills_.rows / 2); i < pills_.rows; i++, n++)
		for (int j = 0, m = -(pills_.cols / 2); j < pills_.cols * 3; j+=3, m++)
			if (game_frame.at<uchar>(n + x, m + y) == 0)
				game_frame.at<uchar>(n + x, m + y) = pills_.at<uchar>(i, j);
}

void Weapon::FindWeapon() {
	oldKnife_ = knife_;
	int max_i = -1, max_j = -1, min_i = 1000000, min_j = 1000000;
	for (int i = 0; i < mask_.cols; i++) {
		for (int j = 0; j < mask_.rows; j++) {
			if (mask_.at<uchar>(j, i) == 255) {
				max_i = std::max(max_i, i);
				max_j = std::max(max_j, j);
				min_i = std::min(min_i, i);
				min_j = std::min(min_j, j);
			}
		}
	}
	if (max_i == -1)
		knife_ = std::make_pair(-1, -1);
	else
		knife_ = std::make_pair((min_i + max_i) / 2, (min_j + max_j) / 2);

	std::cout << knife_.first << "  " << knife_.second << std::endl;
	std::cout << oldKnife_.first << "  " << oldKnife_.second << std::endl << std::endl;
}

void Weapon::WeaponDamage(std::vector<Enemy> &enemies) const {
	for (auto enem = enemies.begin(); enem < enemies.end(); enem++)
		if (sqrt(pow(enem->y_ - knife_.second * 2 + (double)pills_.cols / 2, 2) + pow(enem->x_ - knife_.first * 2 - (double)pills_.rows / 2, 2)) < 30) {
			if (sqrt(pow(enem->y_ - oldKnife_.second * 2 + (double)pills_.cols / 2, 2) + pow(enem->x_ - oldKnife_.first * 2 - (double)pills_.rows / 2, 2)) > 30){
				enem->hp_ -= damage_;
			}
		}
}

Weapon::~Weapon() { }