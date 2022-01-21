#include "Header.h"
#include <opencv2/core/base.hpp>

using namespace cv;
using namespace std;

void Video::createhomogrdet(Mat& img)
{
	vector<Point2f> baseP, makeP;
	int rows = img.rows;
	int cols = img.cols;
	baseP.push_back(Point2f(cols * xn2, rows * yn));
	baseP.push_back(Point2f(cols * xn1, rows * yn));
	baseP.push_back(Point2f(cols * xh1, rows * yh));
	baseP.push_back(Point2f(cols * xh2, rows * yh));

	makeP.push_back(Point2f(cols * hxn2, rows * hyn));
	makeP.push_back(Point2f(cols * hxn1, rows * hyn));
	makeP.push_back(Point2f(cols * hxh1, rows * hyh));
	makeP.push_back(Point2f(cols * hxh2, rows * hyh));

	Mat t = getPerspectiveTransform(baseP, makeP);
	warpPerspective(img, img, t, img.size());
}

void Video::_delbadarea(Mat& img)
{
	int rows = img.rows;
	int cols = img.cols;
	Mat im2(rows, cols, CV_8UC1, Scalar(0));
	Point pt[1][4];
	pt[0][0] = Point(cols * xn2, rows * yn);
	pt[0][1] = Point(cols * xn1, rows * yn);
	pt[0][2] = Point(cols * xh1, rows * yh);
	pt[0][3] = Point(cols * xh2, rows * yh);
	const Point* p[1] = { pt[0] };
	const int npt[] = { 4 };
	fillPoly(im2, p, npt, 1, Scalar(255), 8);
	bitwise_and(img, im2, img);
}

void Video::createbritn(Mat& img, double gamma)
{
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
	LUT(img, lookUpTable, img);
}

void Video::rdatamake(Mat& img)
{
	_rdta.clear();
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	for (int i = 0; i < contours.size(); i++)
	{
		retdata r;
		float g = arcLength(Mat(contours[i]), true);
		approxPolyDP(contours[i], r.dots, g * 0.03, true);
		if (r.dots.size() != 4 || g < arcLparam) continue;
		Moments m = moments(contours[i]);
		r.masscenter = Point(m.m10 / m.m00, m.m01 / m.m00);
		_rdta.push_back(r);
	}
}

Video::Video(float txn1, float txn2, float tyn, float txh1, float txh2, float tyh, float tarcLparam)
{
	xn1 = txn1;
	xn2 = txn2;
	xh1 = txh1;
	xh2 = txh2;
	yn = 1 - tyn;
	yh = 1 - tyh;
	arcLparam = tarcLparam;
	_hpadded = false;
}

void Video::homograph(float txn1, float txn2, float tyn, float txh1, float txh2, float tyh)
{
	_hpadded = true;
	hxn1 = txn1;
	hxn2 = txn2;
	hxh1 = txh1;
	hxh2 = txh2;
	hyn = 1 - tyn;
	hyh = 1 - tyh;
}

bool Video::ishomographactive() { return _hpadded; }

void Video::bind(Mat& image)
{
	Mat im2 = image.clone();
	createbritn(im2, 3);
	cvtColor(im2, im2, COLOR_RGB2GRAY);
	_delbadarea(im2);
	inRange(im2, Scalar(30), Scalar(255), im2);
	cvtColor(image, image, COLOR_RGB2HLS);
	inRange(image, Scalar(0, 130, 0), Scalar(220, 255, 255), image);
	bitwise_and(image, im2, image);
	if (_hpadded) createhomogrdet(image);
	auto kn = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	morphologyEx(image, image, MORPH_OPEN, kn);
	kn = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	morphologyEx(image, image, MORPH_CLOSE, kn);
	Canny(image, image, 50, 250);
	rdatamake(image);
}

vector<retdata> Video::getdata() { return _rdta; }

vector<Point> AdjVideo::dirline(vector<Point> b)
{
	Point2f _a, _b;
	_a.x = 0; _a.y = 0;
	_b.x = 0; _b.y = 0;
	vector<Point> rv;
	bool t[4] = { 0, 0, 0, 0 };
	for (int j = 0; j < 2; j++)
	{
		int l = 0; float low = 0;
		for (int i = 0; i < 4; i++)
		{
			if (b[i].y > low && !t[i])
			{
				l = i;
				low = b[i].y;
			}
		}
		t[l] = true;
	}
	for (int i = 0; i < 4; i++)
	{
		if (t[i])
		{
			_a.x += b[i].x;
			_a.y += b[i].y;
		}
		else
		{
			_b.x += b[i].x;
			_b.y += b[i].y;
		}
	}
	_a = _a / 2; _b = _b / 2;
	rv.push_back(_a); rv.push_back(_b);
	return rv;
}

void AdjVideo::rdatamakef(Mat& img)
{
	_rdta.clear();
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<Point2f> _lvec;
	for (int i = 0; i < contours.size(); i++)
	{
		retdataf f;
		f.isnew = true;
		float g = arcLength(Mat(contours[i]), true);
		approxPolyDP(contours[i], f.dots, g * 0.03, true);
		if (f.dots.size() != 4 || g < arcLparam) continue;
		auto kr = dirline(f.dots);
		f.ln[0] = kr[0]; f.ln[1] = kr[1];
		Moments m = moments(contours[i]);
		f.masscenter = Point(m.m10 / m.m00, m.m01 / m.m00);
		printf("Öåíòð ìàññ ðàñïîçíàííîãî îáúåêòà: x = %.2f  ó = %.2f;\n", m.m10 / m.m00, m.m01 / m.m00, true);
		bool fnd = false;
		for (int j = 0; j < lvec.size(); j++)
		{
			double k = pointPolygonTest(contours[i], lvec[j], true);
			if (k<0 || k * (-1)>dotrange) continue;
			else
			{
				fnd = true;
				f.trackedpoint = lvec[j];
				break;
			}
		}
		if (fnd) f.isnew = false;
		_lvec.push_back(Point2f(f.masscenter));
		_rdta.push_back(f);
	}
	if (_rdta.empty()) return;
	lvec = _lvec;
}

void AdjVideo::fndprew(Mat& img)
{
	if (lvec.empty()) return;
	vector<Point2f> pt, bp;
	vector<uchar> status;
	vector<float> err;
	TermCriteria criteria = TermCriteria((TermCriteria::COUNT)+(TermCriteria::EPS), 10, 0.03);
	calcOpticalFlowPyrLK(_prew, img, lvec, pt, status, err, Size(15, 15), 2, criteria);
	lvec.clear();
	for (int i = 0; i < status.size(); i++)
	{
		if (status[i] == 1) lvec.push_back(pt[i]);
		else bp.push_back(pt[i]);
	}
	pt.clear();
	status.clear();
	for (int i = 0; i < ttm.size(); i++)
	{
		if (--ttm[i].tic == 0 || ttm[i].bdots.empty()) continue;
		vector<Point2f> _bp;
		calcOpticalFlowPyrLK(ttm[i].limg, img, ttm[i].bdots, pt, status, err, Size(15, 15), 2, criteria);
		ttm[i].bdots.clear();
		for (int o = 0; o < status.size(); o++)
		{
			if (status[o] == 1) lvec.push_back(pt[o]);
			else if (ttm[i].tic != 1) ttm[i].bdots.push_back(pt[o]);
		}
	}
	if (!ttm.empty()) ttm.erase(remove_if(ttm.begin(), ttm.end(), [](_trm const& x) -> bool { return (x.tic <= 0); }), ttm.end());
	if (!bp.empty())
	{
		_trm trm;
		trm.tic = tics;
		trm.bdots = bp;
		trm.limg = img.clone();
		ttm.push_back(trm);
	}
	//cout << ttm.size() << " = ttmsize" << endl;
}

AdjVideo::AdjVideo(float txn1, float txn2, float tyn, float txh1, float txh2, float tyh, float tarcLparam, float fpr, int tic) :Video(txn1, txn2, tyn, txh1, txh2, tyh, tarcLparam)
{
	dotrange = fpr;
	tics = tic;
}

void AdjVideo::bind(Mat& image)
{
	Mat im2 = image.clone();
	cvtColor(im2, im2, COLOR_RGB2GRAY);
	equalizeHist(im2, im2);
	createbritn(im2, 3);
	_delbadarea(im2);
	inRange(im2, Scalar(15), Scalar(255), im2);
	imshow("Êîíòóð ðàñïîçíàííûõ îáúåêòîâ", im2);
	cvtColor(image, image, COLOR_RGB2HLS);
	inRange(image, Scalar(0, 125, 0), Scalar(220, 255, 255), image);
	imshow("×åðíî-áåëîå èçîáðàæåíèå", image);
	bitwise_and(image, im2, image);
	if (_hpadded) createhomogrdet(image);
	auto kn = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	morphologyEx(image, image, MORPH_OPEN, kn);
	kn = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	morphologyEx(image, image, MORPH_CLOSE, kn);
	Canny(image, image, 50, 250);
	if (!beg) beg = true;
	else fndprew(image);
	_prew = image;
	rdatamakef(image);
}

vector<retdataf> AdjVideo::getdata() { return _rdta; }
