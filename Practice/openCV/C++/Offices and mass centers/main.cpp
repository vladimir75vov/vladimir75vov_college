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

using namespace cv;
using namespace std;

Mat img;


string input()
{
	setlocale(LC_ALL, "Russian");
	string filename;
	cout << "\nВведите название файла и нажмите enter" << endl;
	cout << "file.jpg" << endl;
	cout << "sf.jpg" << endl;
	cout << "sf2.jpg" << endl;
	cout << "road.png" << endl;
	cout << "lisii.png" << endl;
	cout << "jir.jpg" << endl;
	cout << "jir2.jpg" << endl;

	cin >> filename;

	cout << "\nОткрыть файл: ";
	cout << filename << endl;

	return filename;

}

string inputVid()
{
	setlocale(LC_ALL, "Russian");
	string filename;
	cout << "\nВведите название файла и нажмите enter" << endl;
	cout << "video.mp4" << endl;
	cout << "video1.mp4" << endl;

	cin >> filename;
	cout << "\nОткрыть файл: ";
	cout << filename << endl;

	return filename;
}

string VideoCap() {
	//Открыть веб камеру по умолчанию
	VideoCapture cap(0);

	// Если не получилось, закрыть программу
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video camera" << endl;
		cin.get(); //Ожидание нажатия любой клавиши
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //Получить ширину кадров видео
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //Получить высоту кадров видео



	string window_name = "My Camera Feed";
	namedWindow(window_name); //Создать окно "моя камера"
	auto fps = cap.get(CAP_PROP_FPS); // количество кадров в секунду
	auto delay = 1000 / fps;
	while (true)
	{
		Mat frame;
		auto time = clock();
		bool bSuccess = cap.read(frame); //читать новый кадр из видео 

		//Разрыв цикла while, если кадры не могут быть захвачены
		if (bSuccess == false)
		{
			cout << "Video camera is disconnected" << endl;
			cin.get(); //Ожидание нажатия любой клавиши
			break;
		}


		//показать рамку в созданном окне
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


		//ожидание 10 мс, пока не будет нажата любая клавиша. 
		//Если нажата клавиша «Esc», цикл while прерывается.
		//Если нажата любая другая клавиша, продолжить цикл. 
		//Если в течение 10 мс ни одна клавиша не была нажата, продолжить цикл. 
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

string Image()
{

	string file = input();
	Mat img = imread(file, 1);
	string source_window = file;

	namedWindow(source_window, WINDOW_GUI_EXPANDED);
	imshow(source_window, img);

	Mat src_gray;
	Mat canny_output;

	cvtColor(img, src_gray, COLOR_RGB2GRAY); // перводит изображение в черно-белое
	imwrite("cvtColor.jpg", src_gray); //создает файл черно-белого изображения
	blur(src_gray, src_gray, Size(10, 10)); //размывает изображение
	imwrite("blur.jpg", src_gray); // создает файл размытого изображения

	double otsu_tresh_val = threshold(src_gray, img, 0, 255, THRESH_BINARY | THRESH_OTSU); //определяет яркость серого изображения
	
	double high_tresh_val = 40, lower_tresh_val = 40 * 0.5; //определяет максимумы и минимумы
	cout << "Фильтрация " << otsu_tresh_val << endl;

	Canny(src_gray, canny_output, lower_tresh_val, high_tresh_val, 3); // алгоритм для работы трехканальное изображение

	string source_grey_window = "Серое изображение";
	namedWindow(source_grey_window, WINDOW_GUI_EXPANDED);
	imshow(source_grey_window, canny_output);
	
	imwrite("canny_output.jpg", canny_output); //сохраняет и открывает обработанное изображение

	RNG rng(12345); //задает рандомные цвета из диапозона ниже
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0)); //

	vector<Moments>mu(contours.size()); //создается вектор моментов, куда передается количество контуров, которое зависит от изображения
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false); //часть вектора передается в столбцы массива mu
	}

	vector<Point2f>mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00); // показывается x y векторы
	}

	for (int i = 0; i < contours.size(); i++)
	{
		printf("Контур № %d: центр масс - x = %.2f y = %.2f; длина - %.2a \n", i, mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00, arcLength(contours[i], true)); //2f - количество знаков после запятой, типа float
	}

	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3); //CV_8UC3 - изображение без знака с 3 каналами

	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)); //указывает диапозон цвета, откуда будут браться случайные значения
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point()); //передается картинка, hierarchy - возвращает иерархию внешних контуров и отверстий. 
																				//элементы 2 и 3 иерархии [idx] имеют не более одного из них, не равного -1: то есть 
																				//у каждого элемента либо нет родителя или потомка, либо родителя, но нет потомка, либо потомка, но нет родителя
																				//Элемент с родителем, но без потомка, будет границей отверстия
		circle(drawing, mc[i], 4, color, -1, 5, 0); //выбирается изображение, центр масс, 4 - радиус, цвета, толщина
	}

	namedWindow("Contours", WINDOW_GUI_EXPANDED);
	imshow("Contours", drawing);

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
	cout << "С чем работаем:\n" << endl;
	cout << "image" << endl;
	cout << "video" << endl;
	string choose;
	cin >> choose;
	bool check = true;
	while (check == true)
	{
		if (choose == "image") {
			check = false;
			Image();
		}
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