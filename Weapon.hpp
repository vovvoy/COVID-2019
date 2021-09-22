#ifndef OPENCV_PROJECT_WEAPON_HPP
#define OPENCV_PROJECT_WEAPON_HPP

#include "Enemy.hpp"

class Weapon {
public:
	Weapon(cv::Mat &pills, cv::Mat &pills_mask);
	void FindWeapon();
	void Thread();
	void MoveWeapon(cv::Mat game);
	void WeaponDamage(std::vector<Enemy> &enemies) const;
	std::pair<double, double> &GetKnife();
	std::pair<double, double> &GetOldKnife();
	cv::Mat & GetKinect();
	~Weapon();

private:
	std::pair<double, double> knife_, oldKnife_;
	int minH = 7, maxH = 32, minS = 246, maxS = 255, minV = 200, maxV = 255;
	cv::Mat pills_, hsv_, mask_, kinect_, pillsMask_;
	cv::VideoCapture cap_;
};


#endif //OPENCV_PROJECT_WEAPON_HPP
