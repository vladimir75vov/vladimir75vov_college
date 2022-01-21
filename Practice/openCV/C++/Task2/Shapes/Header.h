#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

typedef struct __retdata
{
	vector<Point> dots;
	Point masscenter;
} retdata;

typedef struct __retdataf
{
	Point ln[2];
	Point masscenter;
	Point2f trackedpoint;
	vector<Point> dots;
	bool isnew;
} retdataf;

class Video
{
protected:

	float xn1, yn, xn2;
	float xh1, yh, xh2;

	float arcLparam;

	float hxn1, hyn, hxn2;
	float hxh1, hyh, hxh2;
	bool _hpadded;
	void createhomogrdet(Mat& img);
	void _delbadarea(Mat& img);
	void createbritn(Mat& img, double gamma = 2.2);
	void rdatamake(Mat& img);
	vector<retdata> _rdta;

public:
	Video(float txn1, float txn2, float tyn, float txh1, float txh2, float tyh, float tarcLparam);
	Video() = delete;
	void homograph(float txn1, float txn2, float tyn, float txh1, float txh2, float tyh);
	bool ishomographactive();
	virtual void bind(Mat& image);
	vector<retdata> getdata();
};

typedef struct __ticrecogmat
{
	Mat limg;
	vector<Point2f> bdots;
	int tic;
}_trm;

class AdjVideo : public Video
{
	vector<Point> dirline(vector<Point> b);
	vector<retdataf> _rdta;
	void rdatamakef(Mat& img);
	void fndprew(Mat& img);
	float dotrange;
	int tics;
	vector<Point2f> lvec;
	vector<_trm> ttm;
	Mat _prew;
	bool beg;

public:
	AdjVideo(float txn1, float txn2, float tyn, float txh1, float txh2, float tyh, float tarcLparam, float fpr, int tic = 3);
	AdjVideo() = delete;
	virtual void bind(Mat& image);
	vector<retdataf> getdata();
};
