#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void replace(ifstream& inputFile, ofstream& outputFile, \
	const char& char1, const char& char2) {
	// replace operation is finished in this single funtion.
	string line;
	while(getline(inputFile, line)) {
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == char1) {
				outputFile << char2;
			} else {
				outputFile << line[i];
			}
		}
		outputFile << endl;
	}
}

void split(string line, vector <char>& chars) {
	// this function splits a string into characters and store them in a vector.
	chars.clear();
	for (int i = 0; i < line.size(); i++) {
		chars.push_back(line[i]);
	}
}

vector < vector <char> > construct_vector(ifstream& inputFile, \
	vector < vector <char> >& lines) {
	// this function turns the input file into a 2d vector.
	// it not only takes a 2d vector as reference for changes but also return a copy.
	string line;
	vector <char> chars;

	while(getline(inputFile, line)) {
		split(line, chars);
		lines.push_back(chars);
	}

	return lines;
}

void print_output(ofstream& outputFile, const vector < vector <char> >& lines) {
	
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[i].size(); j++) {
			outputFile << lines[i][j];
		}
		outputFile << endl;
	}
}

void dilation(ifstream& inputFile, ofstream& outputFile, \
	const char& char1, vector < vector <char> >& lines) {

	vector < vector <char> > lines_copy = construct_vector(inputFile, lines);
	bool add = false;

	for (int i = 0; i < lines_copy.size(); i++) {
		for (int j = 0; j < lines_copy[i].size(); j++) {
			if (lines_copy[i][j] == char1) { continue; }

			if ((i - 1 >= 0 && lines_copy[i-1][j] == char1) || \
				(j - 1 >= 0 && lines_copy[i][j-1] == char1) || \
				(i + 1 != lines.size() && lines_copy[i+1][j] == char1) || \
				(j + 1 != lines[0].size() && lines_copy[i][j+1] == char1)) {
				add = true;
			}
			if (add) {
				lines[i][j] = char1; // keeping the copy unchanged.
				add = false; // reset.
			}
		}
	}
	print_output(outputFile, lines);
}

void erosion(ifstream& inputFile, ofstream& outputFile, \
	const char& char1, const char& char2, vector < vector <char> >& lines) {
	// this function's flow is the same as the last one.
	vector < vector <char> > lines_copy = construct_vector(inputFile, lines);
	bool erode = false;

	for (int i = 0; i < lines_copy.size(); i++) {
		for (int j = 0; j < lines_copy[i].size(); j++) {
			if (lines_copy[i][j] != char1) { continue; }

			if ((i - 1 >= 0 && lines_copy[i-1][j] != char1) || \
				(j - 1 >= 0 && lines_copy[i][j-1] != char1) || \
				(i + 1 != lines.size() && lines_copy[i+1][j] != char1) || \
				(j + 1 != lines[0].size() && lines_copy[i][j+1] != char1)) {
				erode = true;
			}
			if (erode) {
				lines[i][j] = char2;
				erode = false;
			}
		}
	}
	print_output(outputFile, lines);
}

int main(int argc, char *argv[]) {

	string tmpS, type;
	char char1, char2;
	vector < vector <char> > lines;

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	istringstream mode(argv[3]);
	istringstream c1(argv[4]);
	mode >> type;	c1 >> tmpS;

	// input arguments validations
	if (!inputFile.good()) {
		cerr << "Cannot open the input file selected: " << argv[1] << "\n";
		return 0;
	}

	if ((type != "replace" && type != "erosion" \
		&& type != "dilation") || \
		(type == "dilation" && argc != 5) || \
		(type != "dilation" && argc != 6) || \
		(tmpS.size() > 1)) {
		cerr << "Invalid input for command line arguments." << " \n";
		return 0;
	} else { char1 = tmpS[0]; }

	if (argc == 6) {
		istringstream c2(argv[5]);	c2 >> tmpS;
		if (tmpS.size() > 1) {
			cerr << "Invalid input for 2nd character." << " \n";
			return 0;
		} else { char2 = tmpS[0]; }
	}

	//operations start
	if (type == "replace") {
		replace(inputFile, outputFile, char1, char2);
	} else if (type == "dilation"){
		dilation(inputFile, outputFile, char1, lines);
	} else if (type == "erosion") {
		erosion(inputFile, outputFile, char1, char2, lines);
	}

	inputFile.close();
	outputFile.close();
	return 1;
}