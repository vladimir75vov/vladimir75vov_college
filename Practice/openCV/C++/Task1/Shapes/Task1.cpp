#include <opencv2/core/core.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <ctime>


# define M_PIl 3.141592653589793238462643383279502884L
//#pragma warning(default:4716)

using namespace cv;
using namespace std;

string inputVid()
{
	setlocale(LC_ALL, "Russian");
	string filename;
	cout << "\nВведите b666b.mp4 и нажмите enter" << endl;

	//cin.getline(filename, 80);
	cin >> filename;
	cout << "\nОткрыть файл: ";
	cout << filename << endl;

	return filename;
}

string VideoCap() {
	//Open the default video camera
	VideoCapture cap(0);

	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video



	string window_name = "My Camera Feed";
	namedWindow(window_name); //create a window called "My Camera Feed"
	auto fps = cap.get(CAP_PROP_FPS); // frames per seconds
	auto delay = 1000 / fps;
	while (true)
	{
		Mat frame;
		auto time = clock();
		bool bSuccess = cap.read(frame); // read a new frame from video 

		//Breaking the while loop if the frames cannot be captured
		if (bSuccess == false)
		{
			cout << "Video camera is disconnected" << endl;
			cin.get(); //Wait for any key press
			break;
		}


		//show the frame in the created window
		imshow(window_name, frame);

		if (frame.channels() != 1) cvtColor(frame, frame, COLOR_RGB2GRAY);
		Mat x, y;
		Sobel(frame, x, CV_16S, 1, 0);
		Sobel(frame, y, CV_16S, 0, 1);
		// модуль собеля
		convertScaleAbs(x, x);
		convertScaleAbs(y, y);
		addWeighted(x, 0.5, y, 0.5, 0, frame); //совмещаем картинки

		imshow("sobel", frame);
		// скорость видео
		double time_work = (clock() - time) * 1000 / CLOCKS_PER_SEC;
		if (time_work > delay - 1) time_work = 1;
		else time_work = delay - time_work;


		////  если обработка собелем больше чем задержка тогда получится отрицательное значение(ошибка)
		//int vidos = waitKey(time_work);
		//if (vidos >= 0) break;

		//wait for for 10 ms until any key is pressed.  
		//If the 'Esc' key is pressed, break the while loop.
		//If the any other key is pressed, continue the loop 
		//If any key is not pressed withing 10 ms, continue the loop 
		if (waitKey(10) == 27)
		{
			cout << "Esc key is pressed by user. Stoppig the video" << endl;
			break;
		}
	}
	cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
	cout << "Задержка в мс = " << delay << endl;
	waitKey(0);
	return 0;
}


string Video()
{
	string file = inputVid();
	VideoCapture cap(file);
	if (!cap.isOpened()) {
		cout << "Ошибка открытия файла";
	}

	Mat im;
	for (;;) {
		Mat mat, frame;
		cap >> frame;
		mat = frame;
		if (mat.empty()) break;

		imshow("Распознавание", frame);
		if (waitKey(30) >= 0) break;
	}
	waitKey(0);
	return 0;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "video" << endl;
	string choose;
	cin >> choose;
	bool check = true;
	while (check == true)
	{

		if (choose == "video") {
			check = false;
			//Video();
			VideoCap();
		}
		else {
			check = true;
			cout << "повторите попытку." << endl;
		}
	}
	return 0;
}
