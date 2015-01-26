
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"
#include "opencv2/stitching/warpers.hpp"

using namespace cv;
using namespace std;

string getfilename(string path);
int cutimage(string path);
int stitching();

int main(int argc, char** argv) {

	cutimage("/home/wathmal/Desktop/imgs/image2.jpg");
	return 0;
}


int stitching(){

	/*
	 * use function ars to init.
	 */

	bool try_use_gpu = true;
	vector<Mat> imgs;
	string result_name = "res.jpg";

	Mat img1 = imread("/home/wathmal/Desktop/imgs/image1.jpg");
	Mat img2 = imread("/home/wathmal/Desktop/imgs/image2.jpg");
	Mat img3 = imread("/home/wathmal/Desktop/imgs/image3.jpg");

	imgs.push_back(img1);
	imgs.push_back(img2);
	imgs.push_back(img3);

	Mat pano;

	Stitcher stitcher= Stitcher::createDefault(try_use_gpu);
	stitcher.estimateTransform(imgs);
	Stitcher::Status status= stitcher.composePanorama(pano);
	//Stitcher::Status status= stitcher.stitch(imgs,pano);

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

int cutimage(string path){
	string filename= getfilename(path);
	Mat image= imread(path);


	Size imsize= image.size();
	Rect roi1(0,0, imsize.width /2, imsize.height);
	Rect roi2(imsize.width /2, 0,imsize.width /2, imsize.height);

	Mat croppedimg1= image(roi1).clone();
	Mat croppedimg2= image(roi2).clone();

	namedWindow("showimg",CV_WINDOW_KEEPRATIO);

	//save cropped images

	cout << "saving images ./cropped/" << filename << "_1"<<endl;
	imwrite("./cropped/"+filename+"_1.jpg",croppedimg1);

	cout << "saving images ./cropped/" << filename << "_2"<<endl;
	imwrite("./cropped/"+filename+"_2.jpg",croppedimg2);

	cout << "displaying image";
	imshow("showimg", croppedimg1);
	waitKey(0);
	return 0;

}

string getfilename(string path){
	/*
	 * assuming all images are in jpg format
	 *
	 */
	string token= path.substr(path.find_last_of("/")+1, path.size());
	token= token.substr(0,token.size()-4);

	//cout << token << endl;
	//cout << token.size() << endl;
	return token;
}
