#include "Game.hpp"
#include <thread>

Game::Game() {
	std::map<std::string, std::string> images_name = {
			{"back_ground", "images/back_ground.jpg"},
			{"virus", "images/virus.png"},
			{"pills", "images/pills.png"},
			{"virus_mask", "images/virus_mask.png"},
			{"pills_mask", "images/pills_mask.png"},
			{"digits", "images/digits.jpg"},
	};

	images_ = {
			{"back_ground", cv::imread(images_name["back_ground"])},
			{"virus", cv::imread(images_name["virus"])},
			{"pills", cv::imread(images_name["pills"])},
			{"virus_mask", cv::imread(images_name["virus_mask"])},
			{"pills_mask", cv::imread(images_name["pills_mask"])},
			{"digits", cv::imread(images_name["digits"])},
	};
	cap_.open(1);
	cap_.set(cv::CAP_PROP_FPS, 30);
	frame_ = images_["back_ground"].clone();
}

void CallBackFunc(int event, int x, int y, int flags, void *userdata) {
	std::pair<double, double> *coordinates;
	coordinates = static_cast<std::pair<double, double> *>(userdata);
	if ( event == cv::EVENT_MOUSEMOVE ) {
		coordinates->first = x;
		coordinates->second = y;
	}
}

int Game::KeyCodes(int key){
	if (key == 27)
		return 1;
	if (key == 'p'){
		cv::Mat pause = frame_.clone();
		blur(pause, pause, cv::Size(14, 14), cv::Point(-1, -1));
		cv::putText(pause, "Pause!!!", cv::Point(pause.rows / 2 + 100, pause.cols / 4), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255), 2);
		imshow("game", pause);
		while(cv::waitKey(1) != 'p');
	}
	return 0;
}

void Game::IsGameEnded() {
	if (isGameEnded_) {
		cv::blur(frame_, frame_, cv::Size(14, 14), cv::Point(-1, -1));
		cv::putText(frame_, "GameOver!!!", cv::Point(frame_.rows / 2, frame_.cols / 6), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255), 2);
		cv::putText(frame_, "Your score is " + std::to_string(score_), cv::Point(frame_.rows / 2 + 40, frame_.cols / 4), cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(255), 2);
		imshow("game", frame_);
		cv::waitKey();
	}
}




void Game::Run() {
	time_t start, end;
	Weapon Pills(images_["pills"], images_["pills_mask"]);
	cv::namedWindow("game", 1);
	Enemy Virus(images_["virus"], images_["virus_mask"], "images/teleport1.mp4");

	enemyBurn_ = std::time(nullptr);
	std::time(&start);
	std::time(&Virus.GetTime());
	srand((unsigned) time(nullptr));
	while (!isGameEnded_){
		num_frames_++;
		cap_ >> Pills.kinect_;

		Pills.FindWeapon();Virus.Thread(frame_);
		frame_ = images_["back_ground"].clone();
		Pills.MoveWeapon(frame_);
		Virus.IterateEnemies(frame_, images_["digits"], Pills.oldKnife_, Pills.knife_, score_, isGameEnded_);
		cv::putText(frame_, "score: " + std::to_string(score_), cv::Point(10, 20), cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(0), 2);
		Virus.EnemyHP(frame_, Pills.knife_, Pills.oldKnife_);
		if (std::time(nullptr) - enemyBurn_ > 1) {
			Virus.Teleport(frame_.clone());
			double x = 640, y = 360;
			Virus.DrawEnemy(frame_, x, y);
			Virus.DrawHP(frame_, 640, 360, 100);
			enemyBurn_ = std::time(&enemyBurn_);
		}

		imshow("game", 	frame_);
		if (KeyCodes(cv::waitKey(1)))
			break;
		Virus.ClearEnemies();
	}

	IsGameEnded();

	time(&end);
	double seconds = difftime(end, start);
	std::cout << "FRAME NUMBER -> " << num_frames_ << std::endl << "SECONDS -> " << seconds << std::endl << "FRAME RATE -> " << num_frames_ / seconds << std::endl;
}


Game::~Game() { }