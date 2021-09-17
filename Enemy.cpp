#include "Enemy.hpp"

#include <utility>
//#include <thread>

Enemy::Enemy(cv::Mat &enemy, cv::Mat &enemy_mask, const std::string &teleport) {
	enemy_ = enemy;
	enemyMask_ = enemy_mask;
	cap_.open(teleport);
}

void Enemy::Teleport(cv::Mat &game) {
	cv::Mat video;
	while (true) {
		cap_ >> video;
		if (video.empty()){
			cap_.set(cv::CAP_PROP_POS_AVI_RATIO, 0.0);
			break ;
		}
		for (int i = 0; i < video.cols; i++) {
			for (int j = 0; j < video.rows; j++) {
				cv::Vec3b black = video.at<cv::Vec3b>(cv::Point(i, j));
				if (black[1] < 232 && black[2] < 232 && black[0] < 232) {
					cv::Vec3b &fr = game.at<cv::Vec3b>(game.rows / 2 - video.rows / 2 + j,
													   game.cols / 2 - video.cols / 2 + i);
					fr[0] = black[0];
					fr[1] = black[1];
					fr[2] = black[2];
				}
			}
		}
		imshow("game", game);
		cv::waitKey(2);
	}
}

void Enemy::FindEnemy(const cv::Mat &game) {
	for (int x = 0; x < game.cols; x++) {
		for (int y = 0; y < game.rows; y++) {
			cv::Vec3b back = game.at<cv::Vec3b>(cv::Point(x, y));
			cv::Vec3b back1 = game.at<cv::Vec3b>(cv::Point(x, y + 1));
			cv::Vec3b back2 = game.at<cv::Vec3b>(cv::Point(x, y));
			cv::Vec3b back3 = game.at<cv::Vec3b>(cv::Point(x, y + 1));
			if (back[0] == 251 && back[1] == 158 && back[2] == 213 &&
				back1[0] == 250 && back1[1] == 149 && back1[2] == 208)
				enemies_.insert(std::make_pair(100, std::make_pair(x + 25, y - 2)));
			if (back3[0] == 251 && back3[1] == 154 && back3[2] == 210 &&
				back2[0] == 250 && back2[1] == 145 && back2[2] == 208)
				enemies_.insert(std::make_pair(100, std::make_pair(x - 24, y + 4)));
		}
	}
	std::set<std::pair<double, std::pair<double, double>>> tmp;
	for (auto & it : enemies_) {
		for (int hp = it.second.first + 25, color = 105; hp >= it.second.first - 25; hp--, color += 3){
			cv::Vec3b health = game.at<cv::Vec3b>(it.second.second - 28, hp);
//			std::cout << color << std::endl;
			if (health[0] == 0 && health[1] == 165 && health[2] == color) {
				tmp.insert(std::make_pair((255 - color) / 3, std::make_pair(it.second.first, it.second.second)));
				break ;
			}
		}
	}
	enemies_.clear();
	enemies_ = tmp;
}

void Enemy::Thread(cv::Mat frame, std::thread &t) {
	t = std::thread(&Enemy::FindEnemy, this, frame);
//	t.detach();
//	t.join();
}

void Enemy::DirectEnemy(std::pair<double, std::pair<double, double>> &enemy, double &x, double &y) {
	double angle;
	angle = rand() % 360;
	x = enemy.second.first + cos(angle) * 5;
	y = enemy.second.second + sin(angle) * 5;
}

void Enemy::MoveEnemy(std::pair<double, std::pair<double, double>> &enemy, double &x, double &y) {
	double length = sqrt(pow(enemy.second.first - 640.0, 2) + pow(enemy.second.second - 360.0, 2));
	double vx, vy;
	vx = (enemy.second.first - 640.0) / length;
	vy = (enemy.second.second - 360.0) / length;
	x = enemy.second.first + vx * 5;
	y = enemy.second.second + vy * 5;
}

void Enemy::ChangeScore(const cv::Mat &game, const cv::Mat &digits, int &score, bool flag) {
	int cnt = 3;
	std::set<std::pair<int, int>> coor;
	cv::Mat crop = game(cv::Rect(80,0, 300, 25));
	cv::Mat mask;
	cv::inRange(crop, 0, 0, mask);
	cv::Mat img = cv::Mat::zeros(80,400, CV_8U);

	for (int i = 50, x = 0; i < 300; i++, x++)
		for (int j = 30, y = 0; j < 80, y < 25; j++, y++)
			img.at<uchar>(j, i) = (int)mask.at<uchar>(y, x);


	for (int i = 0; i < 10; i++, cnt += 15) {
		cv::Mat digit = digits(cv::Rect(cnt, 0, 12, 25));
		cv::Mat gray, result, bla;
		cv::cvtColor(digit, gray, cv::COLOR_BGR2GRAY);
		cv::matchTemplate(img, gray, result, cv::TM_SQDIFF_NORMED);
		result.row(30).convertTo(bla, CV_32F);
		for (int x = 73; x < 206; x += 15)
			if (bla.at<float>(0, x) < 0.01)
				coor.insert(std::make_pair(x, i));
	}

	for (const auto & it : coor)
		score = score * 10 + it.second;

	if (flag)
		score++;

}

void Enemy::IterateEnemies(const cv::Mat &game, const cv::Mat &digits, std::pair<double, double> oldKnife_,
						   std::pair<double, double> knife_, int &score, bool &isGameEnded) {
	double x, y;
	std::set<std::pair<double, std::pair<double, double>>> tmp;
	for (auto & it : enemies_) {
		if (it.second.first == 640 && it.second.second == 360)
			DirectEnemy(const_cast<std::pair<double, std::pair<double, double>> &>(it), x, y);
		else
			MoveEnemy(const_cast<std::pair<double, std::pair<double, double>> &>(it), x, y);

		if (x + 25 < game.cols && x > 25 && y < game.rows - 25 && y > 25) {
			if (it.first - 20 <= 0){
				ChangeScore(game, digits, score, true);
			} else if (it.first - 20 > 0) {
				DrawEnemy(game, x, y);
				tmp.insert(std::make_pair(it.first, std::make_pair(x, y)));
			}
		} else {
			isGameEnded = true;
			break ;
		}
	}
	if (tmp.size()){
		enemies_.clear();
		enemies_ = tmp;
	}
}

void Enemy::DrawHP(const cv::Mat &game, double x, double y, int hp) {
	if (x == 640 && y == 360)
		for (int i = x - 25, color = 255; i <= x + 25.999; i++, color -= 3){
			for (int j = y - 30; j < y - 27; j++){
				cv::Vec3b &hp = const_cast<cv::Vec3b &>(game.at<cv::Vec3b>(j, i));
				hp[0] = 0;
				hp[1] = 165;
				hp[2] = color;
			}
		}
	else
		for (int i = x - 25, color = 255; i < x + (hp - 25) + 0.999; i++, color -= 3){
			for (int j = y - 30; j < y - 27; j++){
				cv::Vec3b &hp = const_cast<cv::Vec3b &>(game.at<cv::Vec3b>(j, i));
				hp[0] = 0;
				hp[1] = 165;
				hp[2] = color;
			}
		}
}

void Enemy::DrawEnemy(const cv::Mat &game, double &x, double &y) {
	enemy_.copyTo(game(cv::Rect((int)x - 25, (int)y - 25, 50, 50)), enemyMask_);
}

Enemy::~Enemy(){ }