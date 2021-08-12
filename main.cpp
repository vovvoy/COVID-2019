#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
int main( int argc, char** argv ) {
	cv::namedWindow( "Example3", cv::WINDOW_AUTOSIZE);
	cv::VideoCapture cap;
	cap.open( "http://10.178.128.208:4747/video" );
//	cap.open(0);
	cv::Mat frame, src, image;
	std::vector<cv::Vec3f> circles;
	for(;;) {
		cap >> frame;
		if( frame.empty() ) break;
		cv::cvtColor(frame, src, cv::COLOR_BGR2GRAY);
		cv::GaussianBlur(src, src, cv::Size(5,5), 0, 0);
		cv::HoughCircles(src, circles, cv::HOUGH_GRADIENT, 2, src.cols/10);
		cv::circle(src,
				   cv::Point(cvRound(circles[0][0]), cvRound(circles[0][1])),
				   cvRound(circles[0][2]),
				   cv::Scalar(0,0,255), 2, cv::LINE_AA
				   );

		//		cv::resize(frame, frame, cv::Size(300, 200));
		cv::flip(frame, frame, -1);
		cv::flip(frame, frame, 0);
		cv::rectangle(frame, cv::Point2i(frame.cols / 2 + 50, frame.rows / 2 + 50), cv::Point2i(frame.cols / 2 - 50, frame.rows / 2 - 50), NULL);
		cv::line(frame, cv::Point2i(0, 0), cv::Point2i(frame.cols - 1, frame.rows - 1), NULL);
		cv::line(frame, cv::Point2i(0, frame.rows - 1), cv::Point2i(frame.cols - 1, 0), NULL);
		cv::imshow( "Example3", frame );
		if( cv::waitKey(33) >= 0 ) break;
		circles.clear();
	}
	return 0;
}
