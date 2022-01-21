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
	cout << "jir.jpg" << endl;
	cout << "jir2.jpg" << endl;

	cin.getline(filename, 80);
	cout << "Открыть файл: ";
	cout << filename << endl;

	Mat img = imread(filename, 1);
	const char* source_window =  filename;

	namedWindow(source_window, WINDOW_GUI_EXPANDED);
	imshow(source_window, img);

	Mat src_gray;
	Mat canny_output;

	cvtColor(img, src_gray, COLOR_RGB2GRAY); // перводит изображение в черно-белое
	imwrite("cvtColor.jpg", src_gray); //создает файл черно-белого изображения
	blur(src_gray, src_gray, Size(10, 10)); //размывает изображение
	imwrite("blur.jpg", src_gray); // создает файл размытого изображения

	double otsu_tresh_val = threshold(src_gray, img, 0, 255, THRESH_BINARY | THRESH_OTSU); //определяет яркость серого изображения
	//double high_tresh_val = otsu_tresh_val, lower_tresh_val = otsu_tresh_val * 0.5;
	double high_tresh_val = 40, lower_tresh_val = 40 * 0.5; //определяет максимумы и минимумы
	cout << "Фильтрация " << otsu_tresh_val << endl;

	Canny(src_gray, canny_output, lower_tresh_val, high_tresh_val, 3); // алгоритм для работы трехканальное изображение

	string source_grey_window = "Серое изображение";
	namedWindow(source_grey_window, WINDOW_GUI_EXPANDED); 
	imshow(source_grey_window, canny_output);
	//dfd
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
	return(0);
}
