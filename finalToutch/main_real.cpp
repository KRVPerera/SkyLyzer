
#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <errno.h>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"
#include "opencv2/stitching/warpers.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int GLOBAL_WIDTH= 1100;

int getdir (string dir, vector<string> &files);
string getfilename(string path);
string stitching(string im1, string im2);

string dir = string("./sample001/");
string savedpath= "./cropped/";
int main(int argc, char** argv) {

	string stitchedpath;
	vector<string> files = vector<string>();

	if( argc > 1){ // command line argument is presrnt
		cout << "Command line argumant: " << argv[1] << endl;
		dir = argv[1];
	}else{ //if command line argumant is not given
		cout << "Directory : ";	
		cin >> dir;
	}

	dir = "./"+dir+"/";
	getdir(dir,files);
	sort(files.begin(),files.end());

	for (unsigned int i = 1;i < files.size()-1;i++) {
		cout << files[i] << endl;
		// now cut image into 2
		if(i==1){
			stitchedpath= stitching(dir+ files[i-1], dir+ files[i]);
			//cutimage(stitchedpath);
			//remove(stitchedpath.c_str());

		}else if( i > 1 ){
			
			stitchedpath= stitching(stitchedpath, dir+ files[i]);

		}
	}



	return 0;
}


string stitching(string im1, string im2){

	/*
	 * this will stitch only 2 images
	 * images must cut into 2 pieces and stitch the 2nd piece of 1st and
	 * 1st piece of 2nd image.
	 * save it.
	 */
	cout << "Hey yo I am Stitching " <<  im1 << " & " << im2 << endl;
	bool try_use_gpu = true;
	vector<Mat> imgs;
	string result_name = dir+ getfilename(im1) + getfilename(im2)+".jpg";

	Mat img1 = imread(im1);
	Mat img2 = imread(im2);
	//Mat img3 = imread("/home/wathmal/Desktop/imgs/image3.jpg");





	imgs.push_back(img1);
	imgs.push_back(img2);
	//imgs.push_back(img3);

	Mat pano;

	Stitcher stitcher= Stitcher::createDefault(try_use_gpu);
	stitcher.estimateTransform(imgs);
	Stitcher::Status status= stitcher.composePanorama(pano);

	//Stitcher::Status status= stitcher.stitch(imgs,pano);

	if(status != Stitcher::OK){
		cout << "can't stitch " << int(status) << endl;
		return "";
	}
	else{

		//namedWindow("mywindow",CV_WINDOW_FREERATIO);
		/*
		while(waitKey() != 27){
			imshow("mywindow",pano);
		}
		*/
		imwrite(result_name,pano);
		return result_name;
	}
}


string getfilename(string path){
	/*
	 * assuming all images are in jpg format
	 *
	 */
	string token= path.substr(path.find_last_of("/")+1, path.size());
	token= token.substr(0,token.size()-4);
	cout << "Inside getfilename: " << token << endl;
	//cout << token << endl;
	//cout << token.size() << endl;
	return token;
}

/*
 * get the files inside the directory
 * to a vector
 */
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
    	string name= string(dirp->d_name);
    	if(name[0] != '.'){
			cout << "Inside getdir: " << name << endl;
    		files.push_back(name);
    	}
    }
    closedir(dp);
    return 0;
}


/*int seqcut(){}*/
