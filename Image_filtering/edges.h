#pragma once

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

class Edges
{
public:
	Edges(Mat ImgIn, int kerSize, int choice);
	Mat getOutImage();
	~Edges();

private:
	//metodi
	void setInputImage(Mat img);
	bool cannyEdge();
	bool sobelEdge();

	//attributi
	int lowThreshold;
	int max_lowThreshold;
	int ratio;
	int ker_size;
	Mat src, dst;

};
