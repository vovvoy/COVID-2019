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
	Weapon(std::string path, int damage);
	void DrawWeapon(int x, int y, cv::Mat &game_frame);
	void FindWeapon();
	void MoveWeapon(cv::Mat game_frame);
	void WeaponDamage(std::vector<Enemy> &enemies) const;
	~Weapon();
	int damage_;
	std::pair<double, double> knife_, oldKnife_;
	cv::Mat knifeImage_, hsv_, mask_, bla_;
	cv::VideoCapture cap_;
};


#endif //OPENCV_PROJECT_WEAPON_HPP
