#include "Game.hpp"

using namespace std;
using namespace cv;

int main( int argc, char** argv ) {
	Game Valhalla("black_hall.mp4", 2.0, 100);
	Valhalla.Run();
	return 0;
}
