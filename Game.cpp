#include "Game.hpp"

Game::Game(std::string black_hall, double speed, int hp) {
	teleport_.open(black_hall);
	hp_ = hp;
	speed_ = speed;
}

int Game::KeyCodes(int key){
	if (key == 27)
		return 1;
	if (key == 'p'){
		blur(game_frame_, game_frame_, cv::Size(14, 14), cv::Point(-1, -1));
		cv::putText(game_frame_, "Pause!!!", cv::Point(game_frame_.rows / 2 + 100, game_frame_.cols / 4), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255), 2);
		imshow("Aliens from valhalla", game_frame_);
		while(cv::waitKey(1) != 'p');
	}
	return 0;
}

void Game::MoveEnemy() {
	for (auto enem = enemies_.begin(); enem < enemies_.end(); enem++)
		if ((enem->x_ + enem->vecX_ * enem->speed_ + (double)enem->enemyImage_.rows / 2 < game_frame_.rows &&
			 enem->x_ + enem->vecX_ * enem->speed_ + (double)enem->enemyImage_.rows / 2 > enem->enemyImage_.rows &&
			 enem->y_ + enem->vecY_ * enem->speed_ + (double)enem->enemyImage_.cols / 2 < game_frame_.cols &&
			 enem->y_ + enem->vecY_ * enem->speed_ + (double)enem->enemyImage_.cols / 2 > enem->enemyImage_.cols) && enem->hp_ > 0) {
			enem->DrawEnemy(game_frame_);
			enem->x_ += enem->vecX_ * enem->speed_;
			enem->y_ += enem->vecY_ * enem->speed_;
		} else if (enem->hp_ < 1){
			enemies_.erase(enem);
			score_++;
		} else {
			isGameEnded_ = true;
		}
}

void Game::DrawTeleport() {
	for (int n = 0, i = game_frame_.rows / 2 - frame_.rows / 2; i <= game_frame_.rows / 2 + frame_.rows / 2; i++, n++)
		for (int m = 0, j = game_frame_.cols / 2 - frame_.cols / 2; j <= game_frame_.cols / 2 + frame_.cols / 2; j++, m += 3)
			if (frame_.at<uchar>(n, m) > 80 && game_frame_.at<uchar>(i, j) == 0)
				game_frame_.at<uchar>(i, j) = frame_.at<uchar>(n, m);
}

void Game::Run() {
	time_t start, end;
	Weapon Knife("knife.jpg", 40);
	Knife.cap_.set(cv::CAP_PROP_FPS, 30);
	enemyBurn_ = std::time(nullptr);
	time(&start);
	cv::Mat frame;
	srand((unsigned) time(nullptr));
	while (!isGameEnded_){
		num_frames_++;
		game_frame_ = cv::Mat::zeros(720,1280, CV_8U);
//		cv::resize(game_frame_, frame, cv::Size(1280, 720), cv::INTER_LINEAR);
		teleport_ >> frame_;
		Knife.cap_ >> Knife.bla_;
		cv::flip(Knife.bla_, Knife.bla_, 1);
		cv::cvtColor(Knife.bla_, Knife.hsv_, cv::COLOR_BGR2HSV);
		cv::inRange(Knife.hsv_, cv::Scalar(minH, minS, minV),
					cv::Scalar(maxH, maxS, maxV), Knife.mask_);
		if (frame_.empty()){
			teleport_.set(cv::CAP_PROP_POS_AVI_RATIO, 0.0);
			continue ;
		}
		cv::pyrDown(frame_, frame_);
		cv::pyrDown(frame_, frame_);
		if (frame_.empty())
		{
			std::cout << "Video camera is disconnected" << std::endl;
			break;
		}
		cv::putText(game_frame_, "score: " + std::to_string(score_), cv::Point(10, 20), cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(255), 2);
		if (std::time(nullptr) - enemyBurn_ > 2) {
			Enemy Enem("virus.png", game_frame_.rows / 2, game_frame_.cols / 2, speed_, std::rand() % 360, 100);
			enemies_.push_back(Enem);
			enemyBurn_ = std::time(nullptr);
		}
		MoveEnemy();
		Knife.FindWeapon();
		Knife.MoveWeapon(game_frame_);
		DrawTeleport();
		Knife.WeaponDamage(enemies_);
		imshow("Aliens from valhalla", 	game_frame_);
		int key = cv::waitKey(1);
		if (KeyCodes(key))
			break;
	}

	if (isGameEnded_) {
		cv::blur(game_frame_, game_frame_, cv::Size(14, 14), cv::Point(-1, -1));
		cv::putText(game_frame_, "GameOver!!!", cv::Point(game_frame_.rows / 2, game_frame_.cols / 6), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255), 2);
		cv::putText(game_frame_, "Your score is " + std::to_string(score_), cv::Point(game_frame_.rows / 2 + 40, game_frame_.cols / 4), cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(255), 2);
		imshow("Aliens from valhalla", game_frame_);
		cv::waitKey();
	}
	time(&end);
	double seconds = difftime(end, start);
	std::cout << "FRAME NUMBER -> " << num_frames_ << std::endl << "SECONDS -> " << seconds << std::endl << "FRAME RATE -> " << num_frames_ / seconds << std::endl;
}


Game::~Game() { }