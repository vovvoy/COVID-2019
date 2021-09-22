#include "Weapon.hpp"
#include <vector>

Weapon::Weapon(cv::Mat &pills, cv::Mat &pills_mask) {
	pills_ = pills;
	pillsMask_ = pills_mask;
}



void Weapon::MoveWeapon(cv::Mat game) {
	if (knife_.first * 2 + 25 < game.cols - 10 && knife_.first * 2 + 25 > 50 && knife_.second * 1.5 + 25 < game.rows && knife_.second * 1.5 + 25 > 50) {
		pills_.copyTo(game(cv::Rect(knife_.first * 2 - 25, knife_.second * 1.5 - 25, pills_.cols, pills_.rows)), pillsMask_);
	}
}

std::pair<double, double> &Weapon::GetKnife() {
	return knife_;
}

std::pair<double, double> &Weapon::GetOldKnife() {
	return oldKnife_;
}

cv::Mat &Weapon::GetKinect() {
	return kinect_;
}


void Weapon::FindWeapon() {
	cv::flip(kinect_, kinect_, 1);
	cv::cvtColor(kinect_, hsv_, cv::COLOR_BGR2HSV);
	cv::inRange(hsv_, cv::Scalar(minH, minS, minV),
				cv::Scalar(maxH, maxS, maxV), mask_);
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
		knife_ = std::make_pair((min_i + max_i), (min_j + max_j) * 0.75);

}

Weapon::~Weapon() { }