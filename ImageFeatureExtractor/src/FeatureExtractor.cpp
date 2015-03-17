/**
 * Author: Adarsh Jois
 *
 */
#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <ostream>
#include <time.h>
#include <fstream>
#include "FeatureVec.h"
using namespace cv;
using namespace std;

struct csv_rec {
	string file_name;
	string label;
};

bool verbose = false;

bool is_number(const std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}

vector<csv_rec> parse_csv(string prepend_path, ifstream &csv_file) {
	vector<csv_rec> recs;

	while (!csv_file.eof()) {
		string line;
		getline(csv_file, line);

		int comma_pos = line.find(',', 0);

		if (csv_file.eof()) {
			break;
		}
		string name = line.substr(0, comma_pos);
		if (verbose)
			cout << "filename: " << name << endl;
		string label = line.substr(comma_pos + 1);
		if (verbose)
			cout << "label: " << label << endl;
		csv_rec r = { prepend_path + name, label };
		recs.push_back(r);
	}
	//get rid of first line containing title and some stuff
	recs.erase(recs.begin());
	return recs;

}
int write_features_to_file(vector<csv_rec> records, ostream &outfile, int rows,
		int cols) {
	int count = 0;
	FeatureVec::verbose = verbose;
	for (vector<csv_rec>::iterator it = records.begin(); it != records.end();
			it++) {
		if (verbose)
			cout << "Extracting features from " << it->file_name << ","
					<< it->label << endl;
		FeatureVec * fv = NULL;
		if (rows > 0 && cols > 0) {
			fv = new FeatureVec(it->file_name, it->label, rows, cols);
		} else {
			fv = new FeatureVec(it->file_name, it->label);
		}

		if (fv != NULL && fv->isGood()) {
			count++;

			outfile << it->file_name << ", " << it->label << ", ";
			outfile << fv->getFeatures();

			outfile << endl;
		}
	}
	return count;
}
int main(int argc, char**argv) {
	//TODO Add some stuff to handle file extensions, csv might not have them.
	vector<csv_rec> records;
	int rows = 0;
	int cols = 0;

	if (argc < 3) {
		cout
				<< "Usage Downsampler <input_csv_with_labels_and_file_names> <outputfile> [<rows> <colums>] [-v]"
				<< endl;
		return -1;
	}
	if (argc == 6) {
		string s_rows = argv[3];
		string s_columns = argv[4];

		if (is_number(s_rows) && is_number(s_columns)) {
			rows = stoi(s_rows);
			cols = stoi(s_columns);
		} else {
			cout << "Error in args" << endl;
			return -1;
		}
		string v(argv[5]);
		if (v.compare("-v") == 0) {
			verbose = true;
		}
	}
	ifstream csv_file(argv[1]);

	clock_t t1, t2; //timers
	t1 = clock();
	if (csv_file.is_open()) {
		string path_to(argv[1]);
		int pos = path_to.find_last_of('/');
		//build index of files.
		records = parse_csv(path_to.substr(0, pos + 1), csv_file);
	} else {
		cout << "Couldn't open csv. check path, or if file exists" << endl;
		return -1;
	}
	filebuf fb;
	fb.open(argv[2], ios::out);
	int count = 0;
	if (fb.is_open()) {
		ostream outfile(&fb);
		count = write_features_to_file(records, outfile, rows, cols);
		fb.close();
	}
	t2 = clock();
	float diff((float) t2 - (float) t1);
	cout << "Read " << count << " files in " << diff / CLOCKS_PER_SEC
			<< " seconds" << endl;
}
