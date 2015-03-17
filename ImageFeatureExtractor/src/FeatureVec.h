/*
 * FeatureVec.h
 *
 *  Created on: 16-Mar-2015
 *      Author: adarsh
 */

#include <cv.h>
#include <highgui.h>
#include "opencv2/imgproc/imgproc_c.h"
#include <iostream>
#include <ostream>
#include <fstream>
using namespace cv;
using namespace std;
#ifndef FEATUREVEC_H_
#define FEATUREVEC_H_
/*
 * Features extracted from each image
 */
class FeatureVec {
private:
	string file_name; // name of the file.
	Mat im_col; // color format of the image
	Mat im_gray; // gray scale
	Mat im_lap4; // stores the pyramid downsample of im_gray
	bool good;
	string label;
	static Formatter const * csv_formatter;
public:
	FeatureVec(string file_name, string label);
	FeatureVec(string file_name, string label, int rows, int cols);

	void getGrayLaplacianDownSample(stringstream &ss); //keeps appending stuff to a string stream
	string getFeatures(); //returns all the features as a line of a csv
	virtual ~FeatureVec();
	bool isGood();
	static bool verbose;

};

#endif /* FEATUREVEC_H_ */
