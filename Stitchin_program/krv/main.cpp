//cpp standard libraries
#include <iostream>

//open cv libraries
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/stitching/stitcher.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/detail/autocalib.hpp"
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/util.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"

//custom SkyLyzer libraries
#include "libs/crop.hpp"

using namespace cv;
using namespace std;

bool try_use_gpu = true;
vector<Mat> imgs;
string result_name = "res.jpg";

int stitching();
int main(int argc, char** argv) {

 stitching();
}
int stitching(){
	Mat img1 = imread("../../Image_bank/sample001/1.jpg");
	Mat img2 = imread("../../Image_bank/sample001/2.jpg");
	Mat img3 = imread("../../Image_bank/sample001/3.jpg");
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
		/*
		while(waitKey() != 27){
			imshow("mywindow",pano);
		}
		*/
		imwrite(result_name,pano);
		return 0;
	}
}
