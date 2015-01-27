#include <iostream>
#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"

using namespace cv;
using namespace std;

void crop(string img_location,int index){
	
	Mat image = imread(img_location);
	Size imgsize = image.size();
	
	Rect roi1(0,0, imgsize.width /2, imgsize.height);
	Rect roi2(imgsize.width /2, 0,imgsize.width /2, imgsize.height);

	Mat croppedimg1= image(roi1).clone();
	Mat croppedimg2= image(roi2).clone();

	namedWindow("showing1",CV_WINDOW_KEEPRATIO);
	namedWindow("showing2",CV_WINDOW_KEEPRATIO);

	//save cropped images
	string a ="/cropped/1.jpg";
	string b ="/cropped/2.jpg";

	imwrite(a,croppedimg1);
	imwrite(b,croppedimg2);

	imshow("showing1", croppedimg1);
	imshow("showing2", croppedimg2);
	waitKey(0);

}
