#include "Game.hpp"
#include <cmath>
using namespace std;
using namespace cv;


int main( int argc, char** argv ) {
	Game COVID_19;
	COVID_19.Run();
	return 0;
}



//#include <iostream>
//#include <thread>
//#include <vector>
//#include <mutex>
//
//using namespace std;
//
//int counter = 0;
//mutex counter_mutex;
//
//void counterThread(){
//	for (int i = 0; i < 10000000; i++){
//		unique_lock<mutex> counter_lock(counter_mutex);
//		counter++;
//	}
//	return;
//}
//
//int main(){
//	vector<thread> threads;
//	for (int i = 0; i < 4; i++)
//		threads.push_back(thread(counterThread));
//
//	for (int i = 0; i < 4; i++)
//		threads[i].join();
//	cout << counter << endl;
//	return 0;
//}