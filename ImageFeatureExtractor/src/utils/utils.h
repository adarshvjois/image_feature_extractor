#include <cv.h>
#include <highgui.h>
#include "opencv2/imgproc/imgproc_c.h"
#include <iostream>
#include <ostream>
#include <fstream>
using namespace cv;
using namespace std;

bool contourAreaComparator(vector<Point>contour1,vector<Point>contour2);
