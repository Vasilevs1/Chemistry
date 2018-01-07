#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2\core\utility.hpp"
#include "opencv2/features2d.hpp"
using namespace std;
using namespace cv;
bool belongs_to(int curr, int lower, int higher)
{
	if (curr >= lower && curr <= higher)
	{
		return true;
	}
	else return false;
}
int main()
{
	try 
	{
		//hue range [0;179]
		//value and saturation range [0;255]
		unsigned long int metal_pixels = 0;

		int lower_hue = 0, lower_saturation = 0, lower_value = 0;
		cin >> lower_hue >> lower_saturation >> lower_value;

		int higher_hue = 0, higher_saturation = 0, higher_value = 0;
		cin >> higher_hue >> higher_saturation >> higher_value;

		Mat img_input = imread("C:/Users/bfrol/Documents/Visual Studio 2015/Projects/Chemistry_pixels/x64/Debug/photo.jpg"); //input image
		Mat img_hsv; //hsv image
		imshow("Image", img_input);//show image
		cvtColor(img_input, img_hsv, CV_BGR2HSV);//convert to hsv 
		Vec3b color;//color vector
		for (int y = 0; y < img_hsv.rows; y++)
		{
			for (int x = 0; x < img_hsv.cols; x++)
			{
				color = img_hsv.at<Vec3b>(Point(x, y));//get color info of the pixel at (x;y)
				int hue = color.val[0];
				int saturation = color.val[1];
				int value = color.val[2];
				if (belongs_to(hue, lower_hue, higher_hue) && belongs_to(saturation, lower_saturation, higher_saturation) && belongs_to(value, lower_value, higher_value))
					metal_pixels++;
			}
		}
		Mat img_thr;
		inRange(img_hsv, Scalar(lower_hue, lower_saturation, lower_value), Scalar(higher_hue, higher_saturation, higher_value), img_thr);
		cout << "pixels detected: " << metal_pixels << endl;
		cout << "area occupied: " << (100 * metal_pixels) / (img_hsv.rows * img_hsv.cols) << "%" << endl;
		imshow("Thresholded", img_thr);
		waitKey(0);
	}
	catch (cv::Exception e)
	{
		cerr << e.msg << endl;
	}
	//system("pause");
	return 0;
}