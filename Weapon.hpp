#ifndef OPENCV_PROJECT_WEAPON_HPP
#define OPENCV_PROJECT_WEAPON_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "Enemy.hpp"

typedef struct s_enemy{
	int x;
	int y;
	int angle;
	double vecX;
	double vecY;
	double speed;
	int hp;
} t_enemy;


class Weapon {
public:
	Weapon(cv::Mat &pills, cv::Mat &pills_mask);
	void DrawWeapon(int x, int y, cv::Mat &game_frame);
	void FindWeapon();
	void MoveWeapon(cv::Mat game);
	void WeaponDamage(std::vector<Enemy> &enemies) const;
	~Weapon();
	int damage_;
	void hello(cv::Mat &  frame);
	std::pair<double, double> knife_, oldKnife_;
	cv::Mat pills_, hsv_, mask_, kinect_, pillsMask_;
	cv::VideoCapture cap_;
};


#endif //OPENCV_PROJECT_WEAPON_HPP
