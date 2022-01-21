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
	cout << "¬ведите название файла и нажмите enter" << endl;
	cout << "file.jpg" << endl;
	cout << "sf.jpg" << endl;
	cout << "road.png" << endl;

	cin.getline(filename, 80);
	cout << "ќткрыть файл: ";
	cout << filename << endl;

	Mat img = imread(filename, 1);
	const char* source_window =  filename;

	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, img);

	waitKey(0);
	return(0);

}