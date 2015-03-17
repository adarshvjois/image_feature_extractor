/*
 * FeatureVec.cpp
 *
 *  Created on: 16-Mar-2015
 *      Author: adarsh
 */

#include "FeatureVec.h"

Formatter const * FeatureVec::csv_formatter(cv::Formatter::get("CSV"));
bool FeatureVec::verbose = false;

FeatureVec::FeatureVec(string file_name, string label, int rows, int cols) {
	// loads the file converts it to gray scale
	// interpolates to desired dimensions
	FeatureVec::file_name = file_name;
	FeatureVec::im_col = Mat(rows, cols, CV_8UC3);
	if (verbose) {
		cout << "Resizing to" << rows << " x " << cols << endl;
	}
	Mat img = imread(file_name, 1); // read a color image

	// resize to some uniform width and height cubic interpolation coz its the best
	// but a bit slow
	resize(img, im_col, Size(im_col.rows, im_col.cols), 0, 0, INTER_CUBIC);
	if (!im_col.empty()) {
		cvtColor(FeatureVec::im_col, FeatureVec::im_gray, CV_BGR2GRAY);
		FeatureVec::label = label;
		FeatureVec::good = true;
	} else {
		cout << "Image:: " << file_name << " not found" << endl;
		FeatureVec::good = false;
	}
}

FeatureVec::FeatureVec(string file_name, string label) {
	// loads the file converts it to gray scale
	FeatureVec::file_name = file_name;
	//FeatureVec::im_col = Mat(1280, 720, CV_8UC3);
	Mat img = imread(file_name, CV_LOAD_IMAGE_COLOR);
	FeatureVec::im_col = Mat(img.rows, img.cols, CV_8UC3);
	//resize(img, im_col, Size(im_col.rows, im_col.cols), 0, 0, INTER_CUBIC);
	if (!im_col.empty()) {
		cvtColor(FeatureVec::im_col, FeatureVec::im_gray, CV_BGR2GRAY);
		FeatureVec::label = label;
		FeatureVec::good = true;
	} else {
		cout << "Image:: " << file_name << " not found" << endl;
		FeatureVec::good = false;
	}
}

Mat FeatureVec::getGrayLaplacianDownSample() {

	pyrDown(im_gray, im_lap4);

	Mat line_im_lap4(im_lap4.rows, im_lap4.cols, im_lap4.type());
	line_im_lap4 = im_lap4.reshape(0, 1);
	if (verbose)
		cout << "Final out has dim(" << line_im_lap4.rows << ", "
				<< line_im_lap4.cols << ")" << endl;
	return line_im_lap4;
}

string FeatureVec::getFeatures() {
//returns all the features as a line of a csv
	stringstream ss;
//FEATURE-SET 1
	if (verbose)
		cout << "Extracting getGrayLaplacianDownSample:" << endl;
	csv_formatter->write(ss, getGrayLaplacianDownSample()); //keep writing new features to this stream
	ss << ", " << im_lap4.rows << ", " << im_lap4.cols; //housekeeping, so i know how to reshape this.

//END OF FEATURE-SET1

	return ss.str();

}

bool FeatureVec::isGood() {
	return FeatureVec::good;
}

FeatureVec::~FeatureVec() {
	FeatureVec::im_col.release();
	FeatureVec::im_gray.release();
	FeatureVec::im_lap4.release();
}