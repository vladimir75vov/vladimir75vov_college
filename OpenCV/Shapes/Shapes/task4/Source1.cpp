#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace cv;
using namespace std;
/*
int main()
{
	int height = 520;
	int width = 1500;
	Mat img(height, width, CV_8UC3);
	Point textOrg(10, img.rows / 10);
		int fontFace = FONT_HERSHEY_TRIPLEX;
		double fontScale = 2;
		Scalar color(0, 0, 0);
		putText(img, "smallwhitesaltfatflashlightpussy", textOrg, fontFace, fontScale, color);
		namedWindow("Hello world", 0);
		imshow("HelloWorld", img);
		waitKey(0);
		return 0;
}
*/
Mat img;


int main()	
{
	setlocale(LC_ALL, "Russian");
	char filename[80];
	cout << "Введите название файла и нажмите enter" << endl;
	cout << "file.jpg" << endl;
	cout << "sf.jpg" << endl;
	cout << "sf2.jpg" << endl;
	cout << "road.png" << endl;
	cout << "lisii.png" << endl;

	cin.getline(filename, 80);
	cout << "Открыть файл: ";
	cout << filename << endl;

	Mat img = imread(filename, 1);
	const char* source_window =  filename;

	namedWindow(source_window, WINDOW_GUI_EXPANDED);
	imshow(source_window, img);

	Mat src_gray;
	Mat canny_output;

	cvtColor(img, src_gray, COLOR_RGB2GRAY);
	imwrite("cvtColor.jpg", src_gray);
	blur(src_gray, src_gray, Size(10, 10));
	imwrite("blur.jpg", src_gray);

	double otsu_tresh_val = threshold(src_gray, img, 0, 255, THRESH_BINARY | THRESH_OTSU);
	//double high_tresh_val = otsu_tresh_val, lower_tresh_val = otsu_tresh_val * 0.5;
	double high_tresh_val = 40, lower_tresh_val = 40 * 0.5;
	cout << "Фильтрация " << otsu_tresh_val << endl;

	Canny(src_gray, canny_output, lower_tresh_val, high_tresh_val, 3); // трехканальное изображение

	string source_grey_window = "Серое изображение";
	namedWindow(source_grey_window, WINDOW_GUI_EXPANDED); 
	imshow(source_grey_window, canny_output);
	//dfd
	imwrite("canny_output.jpg", canny_output);

	RNG rng(12345);
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Moments>mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	vector<Point2f>mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	for (int i = 0; i < contours.size(); i++)
	{
		printf("Контур № %d: центр масс - x = %.2f y = %.2f; длина - %.2a \n", i, mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00, arcLength(contours[i], true));
	}
  
  
	waitKey(0);
	return(0);
  
