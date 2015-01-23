#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"
#include "opencv2/stitching/warpers.hpp"

using namespace cv;
using namespace std;

bool try_use_gpu = true;
vector<Mat> imgs;
string result_name = "res.jpg";


int main(int argc, char** argv) {
	
	cout << "Enter output file name: " ;
	cin >> result_name;
	cout << result_name;	
	/*
	Mat image;
	VideoCapture cap;
	cap.open(0);
	namedWindow("window",1);

	// exit on esc
	while(waitKey(1) != 27){
		cap >> image;
		imshow("window", image);

	}
	destroyAllWindows();
	return 0;
	*/

	cout << "bug start" << endl;
	//fill images to vector
	Mat img1 = imread("~/Desktop/myOpencvAttempt/opencvtest/imgs/20150119_104121.jpg");
	Mat img2 = imread("~/Desktop/myOpencvAttempt/opencvtest/imgs/20150119_104127.jpg");
	Mat img3 = imread("~/Desktop/myOpencvAttempt/opencvtest/imgs/20150119_104134.jpg");
	//Mat img4 = imread("/home/wathmal/Desktop/automation challenge 2/boading/f.jpg");
	cout << "bug end" << endl;

	imgs.push_back(img1);
	imgs.push_back(img2);
	imgs.push_back(img3);
	//imgs.push_back(img4);

	Mat pano;
	Stitcher stitcher= Stitcher::createDefault(true);
	stitcher.estimateTransform(imgs);

//	Stitcher::Status status= stitcher.stitch(imgs,pano);
	Stitcher::Status status= stitcher.composePanorama(pano);
	if(status != Stitcher::OK){
		cout << "can't stitch " << int(status) << endl;
		return -1;
	}
	else{

		namedWindow("mywindow",CV_WINDOW_FREERATIO);
		while(waitKey() != 27){
			imshow("mywindow",pano);
		}
		imwrite(result_name,pano);
		return 0;
	}
}
