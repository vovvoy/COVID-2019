//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat imageF(480,720, CV_32FC3);
//	int i = 0;
//	int j = 0;
//	float blue = 0.0;
//	float green= 0.0;
//	float red= 0.0;
//	Vec3f intensity;
//	for (;;) {
//		for (int y = 0; y < 50; y++) {
//			for (int x =  0; x < 50; x++) {
//				// The next two rows do the same
//				//intensity = imageF.at<Vec3f>(y, x);
//				intensity = imageF.at<Vec3f>(Point(x, y));
//
//				blue = red = green = 1;
//				intensity.val[0] = blue;
//				intensity.val[1] = green;
//				intensity.val[2] = red;
//
//				imageF.at<Vec3f>(Point(x, y)) = intensity;
//			}
//		}
//		imshow("Output", imageF);
//
//		char c = waitKey(0);
//		if (c == 27) break;
//	}
//	return 0;
//}



#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	VideoCapture cap;

	cap.open("Black_hall1.mp4");



//	for video writing
//	double fps = cap.get( CAP_PROP_FPS );
//	cv::Size size(
//			(int)cap.get( CAP_PROP_FRAME_WIDTH ),
//			(int)cap.get( CAP_PROP_FRAME_HEIGHT )
//			);
//	VideoWriter writer;
//	writer.open("game_map.mp4", VideoWriter::fourcc('M','P','4','V'), fps, size);


	int frame_count = 0;
	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
	string window_name = "My Camera Feed";
	Mat frame, game_frame;

	game_frame = cv::Mat::zeros(1400,2200, CV_8U);
	for (int i = 0; i < game_frame.rows; i++){
		for (int j = 0; j < game_frame.cols; j++){
			if ( (i >= game_frame.rows / 2 - 250 and i <= game_frame.rows / 2 + 250) and
				(j >= game_frame.cols / 2 - 250 and j <= game_frame.cols / 2 + 250)		)
				continue;
			if (j % 3 == 0)
				game_frame.at<uchar>(i, j) = 20;
			else if (j % 3 == 1)
				game_frame.at<uchar>(i, j) = 23;
			else
				game_frame.at<uchar>(i, j) = 26;
		}
	}
	cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
	namedWindow(window_name); //create a window called "My Camera Feed"
	while (true)
	{
		cap >> frame;
		if (frame.empty()){
			cap.set(CAP_PROP_POS_AVI_RATIO, 0.0);
			continue ;
		}

		if (frame.empty())
		{
			cout << "Video camera is disconnected" << endl;
//			cin.get(); //Wait for any key press
			break;
		}
//		for (int i = 0; i < frame.rows; i++){
//			for (int j = 0; j < frame.cols * 3; j++){
//				int bla = sqrt(pow(i - 250, 2) + pow((j - 750) / 3, 2));
//				if (bla > 250){
////					double color = frame.at<uchar>(i, j);
////					color[0] = 27;
////					color[1] = 29;
////					color[2] = 31;
//					if (j % 3  == 0)
//						frame.at<uchar>(i, j) = 27;
//					else if (j % 3 == 1)
//						frame.at<uchar>(i, j) = 29;
//					else
//						frame.at<uchar>(i, j) = 31;
//					//					cout << color << endl;
//				}
//			}
//		}
//		cv::flip(frame, frame, -1);
//		cv::flip(frame, frame, 0);

//		cv::pyrDown(frame, frame);


//		Rect srcRect(Point(0, 1), Size(frame.cols, 1)); //select the 2nd row
//		Rect dstRect(Point(3, 5), srcRect.size() ); //destination in (3,5), size same as srcRect
//
//		dstRect = dstRect & Rect(Point(0, 0), game_frame.size()); //intersection to avoid out of range
//		srcRect = Rect(srcRect.tl(), dstRect.size()); //adjust source size same as safe destination
//		game_frame(srcRect).copyTo(frame(dstRect)); //copy from (0,1) to (3,5) max allowed cols
		int n = 0, m;
		for (int i = game_frame.rows / 2 - 250; i <= game_frame.rows / 2 + 250; i++, n++){
			m = 0;
			for (int j = game_frame.cols / 2 - 250; j <= game_frame.cols / 2 + 250; j++, m += 3){
				game_frame.at<uchar>(i, j) = frame.at<uchar>(n, m);
			}
		}
		game_frame.copyTo(frame);

		imshow(window_name, frame);
//		writer << frame;
		if (waitKey(10) == 27)
		{
			cout << "Esc key is pressed by user. Stoppig the video" << endl;
			break;
		}
	}
	return 0;

}