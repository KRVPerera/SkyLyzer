
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


using namespace cv;
using namespace std;

int getdir (string dir, vector<string> &files);
string getfilename(string path);
int cutimage(string path);
int stitching(string im1, string im2);

int main(int argc, char** argv) {

	// directory for source images.
	string dir = string("/home/wathmal/Desktop/imgs/rand/");
	vector<string> files = vector<string>();

	getdir(dir,files);
	string croppeddir= "./cropped/";
	sort(files.begin(),files.end());

	for (unsigned int i = 0;i < files.size();i++) {
		cout << files[i] << endl;
		// now cut image into 2
		cutimage(dir+ files[i]);

		//stitching(dir+ files[i], dir+ files[i+1]);



	}
	/*
	 * now the images are cropped
	 * stitch the cropped images by sides.
	 */
	vector<string> croppedfiles= vector<string>();
	getdir(croppeddir, croppedfiles);
	sort(croppedfiles.begin(), croppedfiles.end());
	for (unsigned int i = 0;i < croppedfiles.size();i++) {
		//cout << files[i] << endl;
		// now cut image into 2
		if(i%2 == 1){
			stitching(croppeddir+ croppedfiles[i], croppeddir+ croppedfiles[i+1]);
		}

	}
	//stitching("./cropped/image2_2.jpg","./cropped/image3_1.jpg");
	return 0;
}


int stitching(string im1, string im2){

	/*
	 * this will stitch only 2 images
	 * images must cut into 2 pieces and stitch the 2nd piece of 1st and
	 * 1st piece of 2nd image.
	 * save it.
	 */
	cout << im1 << " & " << im2 << endl;
	bool try_use_gpu = true;
	vector<Mat> imgs;
	string result_name = getfilename(im1) + getfilename(im2)+".jpg";

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
		return -1;
	}
	else{

		//namedWindow("mywindow",CV_WINDOW_FREERATIO);
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

	//cout << "displaying image";
	//imshow("showimg", croppedimg1);
	//waitKey(0);
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
    		files.push_back(name);
    	}
    }
    closedir(dp);
    return 0;
}
