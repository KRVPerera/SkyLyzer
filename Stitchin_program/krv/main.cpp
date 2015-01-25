
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

int stitching();
int main(int argc, char** argv) {

	Mat image= imread("/home/wathmal/Desktop/imgs/image1.jpg");
	Size imsize= image.size();

	Rect roi1(0,0, imsize.width /2, imsize.height);
	Rect roi2(imsize.width /2, 0,imsize.width /2, imsize.height);

	Mat croppedimg1= image(roi1).clone();
	Mat croppedimg2= image(roi2).clone();

	namedWindow("showimg",CV_WINDOW_KEEPRATIO);

	//save cropped images

	imwrite("./cropped/image1.jpg",croppedimg1);
	imwrite("./cropped/image2.jpg",croppedimg2);


	imshow("showimg", croppedimg1);
	waitKey(0);
	return 0;

}


int stitching(){
	Mat img1 = imread("/home/wathmal/Desktop/imgs/image1.jpg");
	Mat img2 = imread("/home/wathmal/Desktop/imgs/image2.jpg");
	Mat img3 = imread("/home/wathmal/Desktop/imgs/image3.jpg");
	//Mat img4 = imread("/home/wathmal/Desktop/automation challenge 2/boading/f.jpg");

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
