#include "Weapon.hpp"
#include <cmath>
#include <iostream>
#include <vector>

Weapon::Weapon(std::string path, int damage) {
	damage_ = damage;
	this->cap_.open(0);
	this->knifeImage_ = cv::imread(path);
}

void Weapon::MoveWeapon(cv::Mat game_frame) {
	if (knife_.first * 2 + (double)knifeImage_.rows / 2 < game_frame.rows && knife_.first * 2 - (double)knifeImage_.rows / 2 >= 0 &&
		knife_.second * 2 + (double)knifeImage_.cols / 2 < game_frame.cols && knife_.second * 2 - (double)knifeImage_.cols / 2 >= 0) {
		DrawWeapon((int) (knife_.first * 2), (int) (knife_.second * 2), game_frame);
	}
}


void Weapon::DrawWeapon(int x, int y, cv::Mat &game_frame) {
	for (int i = 0, n = -(knifeImage_.rows / 2); i < knifeImage_.rows; i++, n++)
		for (int j = 0, m = -(knifeImage_.cols / 2); j < knifeImage_.cols * 3; j+=3, m++)
			if (game_frame.at<uchar>(n + x, m + y) == 0)
				game_frame.at<uchar>(n + x, m + y) = knifeImage_.at<uchar>(i, j);
}

void Weapon::FindWeapon() {
	oldKnife_ = knife_;
	int max_i = -1, max_j = -1, min_i = 1000000, min_j = 1000000;

	for (int i = 0; i < mask_.rows; i++)
		for (int j = 0; j < mask_.cols; j++)
			if (mask_.at<uchar>(i, j) == 255) {
				max_i = std::max(max_i, i);
				max_j = std::max(max_j, j);
				min_i = std::min(min_i, i);
				min_j = std::min(min_j, j);
			}
	if (max_i == -1)
		knife_ = std::make_pair(-1, -1);
	else
		knife_ = std::make_pair((min_i + max_i) / 2, (min_j + max_j) / 2);
}

void Weapon::WeaponDamage(std::vector<Enemy> &enemies) const {
	for (auto enem = enemies.begin(); enem < enemies.end(); enem++)
		if (sqrt(pow(enem->y_ - knife_.second * 2 + (double)knifeImage_.cols / 2, 2) + pow(enem->x_ - knife_.first * 2 - (double)knifeImage_.rows / 2, 2)) < 30) {
			if (sqrt(pow(enem->y_ - oldKnife_.second * 2 + (double)knifeImage_.cols / 2, 2) + pow(enem->x_ - oldKnife_.first * 2 - (double)knifeImage_.rows / 2, 2)) > 30){
				enem->hp_ -= damage_;
			}
		}
}











Weapon::~Weapon() { }