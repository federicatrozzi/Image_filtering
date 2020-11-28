#include "pch.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "edges.h"
#include <stdio.h>

using namespace cv;
using namespace std;

Edges::Edges(Mat ImgIn, int kerSize,int choice)
{
	//inizializzo i parametri a quelli di default
	lowThreshold = 25;
	max_lowThreshold = 100;
	ratio = 3;

	//leggo le dimensioni del kernel
	ker_size = kerSize;

	//set input image
	setInputImage(ImgIn);

	dst = Scalar::all(0);

	if (choice==1)
	{
		cannyEdge();
	}
	else if (choice==2)
	{
		sobelEdge();
	}

}

Edges::~Edges()
{

}

void Edges::setInputImage(Mat img) {
	src = img.clone();
}

Mat Edges::getOutImage() {	
	Mat out = dst.clone();
	return out;
}

bool Edges::cannyEdge() {

	try
	{
		Mat src_gray, detected_edges;
		cvtColor(src, src_gray, COLOR_BGR2GRAY);
		blur(src_gray, detected_edges, Size(ker_size, ker_size));

		Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, ker_size);

		src.copyTo(dst, detected_edges);

		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}

}

bool Edges::sobelEdge() {
	//x_order: The order of the derivative in x direction.
	// y_order : The order of the derivative in y direction.
	// To calculate the gradient in x direction we use : x_order = 1 and y_order = 0.
	// To calculate the gradient in x direction we use : x_order = 0 and y_order = 1.

	try
	{
		Mat src_gray, detected_edges_x, detected_edges_y,grad;
		cvtColor(src, src_gray, COLOR_BGR2GRAY);
		blur(src_gray, src_gray, Size(ker_size, ker_size));

		Sobel(src_gray, detected_edges_x, CV_8UC1, 1, 0, ker_size);

		Sobel(src_gray, detected_edges_y, CV_8UC1, 0, 1, ker_size);

		// converting back to CV_8U
		convertScaleAbs(detected_edges_x, detected_edges_x);
		convertScaleAbs(detected_edges_y, detected_edges_y);


		addWeighted(detected_edges_x, 0.5, detected_edges_y, 0.5, 0, grad);
		src.copyTo(dst, grad);

		return true;
	}
	catch (const std::exception&)
	{

	}


}