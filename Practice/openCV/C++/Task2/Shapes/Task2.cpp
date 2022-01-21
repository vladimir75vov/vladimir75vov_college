#include "Header.h"
#include <chrono>
#include <fstream>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main() {
	// устанвливаем русскую локаль для консоли
	setlocale(LC_ALL, "Russian");

	//char filename[100]; // videoreg.mp4 
	//cout << "Введите имя файла, который хотите проанализировать, и нажмите Enter" << endl;
	//cin.getline(filename, 100);
	//cout << "Открыт файл ";
	//cout << filename << endl;

	VideoCapture cap(0);
	if (!cap.isOpened()) cout << "Ошибка открытия видеофайла" << endl;
	Mat im;
	AdjVideo vid(0.2, 0.8, 0.04, 0.4, 0.6, 0.25, 50, 20);
	vid.homograph(0.2, 0.8, 0.04, 0.4, 0.6, 0.25);
	for (; ;)
	{
		auto beg = chrono::high_resolution_clock::now();
		Mat frame;
		cap >> frame;
		Mat tk = frame.clone();
		if (frame.empty()) break;
		vid.bind(frame);
		auto t = vid.getdata();
		for (int i = 0; i < t.size(); i++)
		{
			line(tk, t[i].ln[0], t[i].ln[1], Scalar(255, 0, 0), 2);
			if (t[i].isnew) putText(tk, "New_object", t[i].ln[0], 2, 1, Scalar(255, 255, 255));
			else
			{
				putText(tk, "centre_mass", t[i].ln[0], 2, 1, Scalar(255, 255, 255));
				drawMarker(tk, t[i].trackedpoint, Scalar(348, 71, 100), 2, 25);
			}
		}
		imshow("Видеорегистратор", tk);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<float> fsec = end - beg;
		auto ms = chrono::duration_cast<chrono::milliseconds>(fsec);
		int tme = ms.count();
		cout << tme << endl;
		if (tme < 30) tme = 30 - tme;
		else tme = 1;
		if (waitKey(tme) >= 0) break;
	}
	return 0;
}
