#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "course.h"

bool is_empty(std::ifstream& file){
	// this function checks if the input file is empty, reference in README.
	return file.peek() == std::ifstream::traits_type::eof();
}

int main(int argc, char *argv[]) {
	std::ifstream inputFile(argv[1]);
	std::ofstream outputFile(argv[2]);
	std::istringstream m(argv[3]);
	std::string mode; m >> mode;
	std::vector<course> classes;
	std::string deptCode;

	// some input arguments validations
	if (!inputFile.good()) {
		std::cerr << "Cannot open the input file selected: " << argv[1] << "\n";
		return 0;
	}
	if (!outputFile.good()) {
		std::cerr << "Error with output file: " << argv[2] << "\n";
		return 0;
	}
	if (argc == 5) {
		std::istringstream n(argv[4]); n >> deptCode;
	} else if (argc != 4) {
		std::cerr << "Incorrect number of input arguments." << "\n";
		return 0;
	} else if (mode != "room" && mode != "dept" && mode != "custom") {
		std::cerr << "Incorrect input argument for output options." << "\n";
		return 0;
	} else if (mode == "dept" && argc != 5) {
		std::cerr << "A 4th argument is required for dept-based output." << "\n";
		return 0;
	}

	if (is_empty(inputFile)) {
		outputFile << "No data available." << std::endl;
		return 1;
	}

	// some helper strings
	std::string crn, dept_code, course_code, course_title, \
		days, time_starts, time_ends, room;

	while(inputFile >> crn >> dept_code >> course_code >> course_title >> \
		days >> time_starts >> time_ends >> room) {
		course _class(crn, dept_code, course_code, course_title, \
			days, time_starts, time_ends, room);
		classes.push_back(_class);
	}

	printClasses(outputFile, classes, mode, deptCode);

	inputFile.close();
	outputFile.close();

	return 1;
}
