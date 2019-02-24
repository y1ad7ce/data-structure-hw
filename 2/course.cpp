#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "course.h"

using namespace std;

course::course(string CRN, string deptCode, string courseCode, string courseTitle, \
	string Days, string timeStarts, string timeEnds, string Room) {

	crn = CRN;
	dept_code = deptCode;
	course_code = courseCode;
	course_title = courseTitle;
	days = Days;
	time_starts = timeStarts;
	time_ends = timeEnds;
	room = Room;

	// info vector avoids calling multiple accessors at some operations.
	info.push_back(crn);
	info.push_back(dept_code);
	info.push_back(course_code);
	info.push_back(course_title);
	info.push_back(days);
	info.push_back(time_starts);
	info.push_back(time_ends);
	info.push_back(room);

	// make start time floats for sorting use.
	string::size_type sz;
	startTime = stof(time_starts.substr(0, 2), &sz) + \
		stof(time_starts.substr(3, 2), &sz) * 0.01;
	if (stoi(time_starts.substr(0, 2), &sz) != 12 && time_starts[5] \
		== 'P') { startTime += 12; }
}

void course::setDay(string day) {
	// this function prepares helper member variable dayNum ready for sorting use.
	days = info[4] = day;
	if (days == "Monday") { dayNum = 1;}
	else if (days == "Tuesday") { dayNum = 2; }
	else if (days == "Wednesday") { dayNum = 3; }
	else if (days == "Thursday") { dayNum = 4; }
	else if (days == "Friday") { dayNum = 5; }
}

bool classSort_room(const course& class1, const course& class2) {
	// sorting order: day -> start time -> course code.
	if (class1.getDayNum() < class2.getDayNum()) {
		return true;
	}
	else if (class1.getDayNum() == class2.getDayNum() && \
		class1.getStartTime() < class2.getStartTime()) {
		return true;
	}
	else if (class1.getDayNum() == class2.getDayNum() && \
		class1.getStartTime() == class2.getStartTime()) {
		return class1.getCourseCode() < class2.getCourseCode();
	}
	return false;
}
bool classSort_dept(const course& class1, const course& class2) {
	// sorting order: course code -> day -> start time
	if (class1.getCourseCode() < class2.getCourseCode()) {
		return true;
	}
	else if ((class1.getCourseCode() == class2.getCourseCode()) && \
		(class1.getDayNum() < class2.getDayNum())) {
		return true;
	}
	else if ((class1.getCourseCode() == class2.getCourseCode()) && \
		(class1.getDayNum() == class2.getDayNum())) {
		return class1.getStartTime() < class2.getStartTime();
	}
	return false;
}
void output_room_ordered(vector<course>& classes, \
	vector<string>& classes_sorted) {
	// this function finds rooms order in output by sorting classrooms' names.
	for (int i = 0; i < classes.size(); i++) {
		classes_sorted.push_back(classes[i].getRoom());
	}
	// make elements sorted and unique. reference in README.
	sort(classes_sorted.begin(), classes_sorted.end());
	classes_sorted.erase( unique( classes_sorted.begin(), \
		classes_sorted.end() ), classes_sorted.end() );
}

vector<course> prepare_classes_vector(vector<course>& classes, \
	string mode) {
	// this function prepares the vector to be ready to print out information.
	// the reason for returning an new vector is expanding original vector.
	// for example, a class' days are MR will become two objects with different day.
	vector<course> newVector;
	string days;

	for (int i = 0; i < classes.size(); i++) {
		days = classes[i].getDays();
		for (int j = 0; j < days.length(); j++) {
			// convert abbr. to words for output.
			if (days[j] == 'M') {
				classes[i].setDay("Monday");
				newVector.push_back(classes[i]);
			} else if (days[j] == 'T') {
				classes[i].setDay("Tuesday");
				newVector.push_back(classes[i]);
			} else if (days[j] == 'W') {
				classes[i].setDay("Wednesday");
				newVector.push_back(classes[i]);
			} else if (days[j] == 'R') {
				classes[i].setDay("Thursday");
				newVector.push_back(classes[i]);
			} else if (days[j] == 'F') {
				classes[i].setDay("Friday");
				newVector.push_back(classes[i]);
			}
		}
	}

	if (mode == "room"){
		sort(newVector.begin(), newVector.end(), classSort_room);
	} else {
		sort(newVector.begin(), newVector.end(), classSort_dept);
	}
	return newVector;
}

void columnsWidths_room(vector<course>& classes, vector< vector<int> >& widths, \
	vector<string>& classes_sorted) {
	// this function calculate the widths of columns of individual rooms in output.
	// each room has different widths of columns. Therefore, "widths" is a 2d vector.
	vector<int> oneClass;
	for (int k = 0; k < classes_sorted.size(); k++) {
		oneClass.clear();
		// Dept + Coursenum + Class Title + Day + Start Time + End Time
		oneClass.push_back(4); oneClass.push_back(9); oneClass.push_back(11);
		oneClass.push_back(3); oneClass.push_back(10); oneClass.push_back(8);
		for (int i = 0; i < classes.size(); i++) {
			if (classes[i].getRoom() != classes_sorted[k]) { continue; }
			for (int j = 1; j < 5; j++) {
				// Dept + Coursenum + Class Title + Day
				// if they present a longer width for any column, replace the number in the vector.
				if (classes[i].getInfo()[j].length() > oneClass[j-1]) {
					oneClass [j-1] = classes[i].getInfo()[j].length();
				}
			}
		}
		widths.push_back(oneClass);
	}
}
void columnsWidths_dept(vector<course>& classes, vector<int>& widths, \
	string deptCode) {
	// similar logic to the last function,
	// but dept output doesn't require a 2d vector since it's only print one department's.
	widths.push_back(4); widths.push_back(9);
	widths.push_back(0); widths.push_back(0);
	widths.push_back(10); widths.push_back(8);
	for (int i = 0; i < classes.size(); i++) {
		for (int j = 3; j < 5; j++) {
			if (classes[i].getDeptCode() == deptCode && \
				classes[i].getInfo()[j].length() > widths[j-1]) {
				widths [j-1] = classes[i].getInfo()[j].length();
			}
		}
	}
}

bool checkIfDeptExist(vector<course>& classes, string& deptCode) {
	bool deptCodeExist = false;
	for (int i = 0; i < classes.size(); i++) {
		if (classes[i].getDeptCode() == deptCode) {
			deptCodeExist = true;
		}
	}
	return deptCodeExist;
}

// two functions for custom output.
void calculations(vector<course>& classes) {
	float StartTime, EndTtime;
	int duration_min;
	string::size_type sz;
	for (int i = 0; i < classes.size(); i++) {
		// calculate total minutes.
		// have start time and end time both converted into minutes(time) of the day.
		// substract and get the interval time.
		EndTtime = stof(classes[i].getTimeEnds().substr(0, 2), &sz) + \
			stof(classes[i].getTimeEnds().substr(3, 2), &sz) * 0.01;
		if (stoi(classes[i].getTimeEnds().substr(0, 2), &sz) != 12 && \
			classes[i].getTimeEnds()[5] == 'P') { EndTtime += 12; }

		StartTime = classes[i].getStartTime();
		duration_min = (((int)(EndTtime * 100))%100 + ((int)EndTtime * 60)) - \
		 (((int)(StartTime * 100))%100 + ((int)StartTime * 60));
		// multiply with number of days in a week.
		classes[i].setDurationTotal(duration_min * classes[i].getDays().length());
	}

	vector<string> class_titles;
	vector<int> times;
	int count_time;
	// correlate two vectors, class titles and class total times
	for (int i = 0; i < classes.size(); i++) {
		class_titles.push_back(classes[i].getCourseTitle());
	}
	sort(class_titles.begin(), class_titles.end());
	class_titles.erase( unique( class_titles.begin(), \
		class_titles.end() ), class_titles.end() );

	for (int j = 0; j < class_titles.size(); j++) {
		count_time = 0;
		for (int i = 0; i < classes.size(); i++) {
			if (classes[i].getCourseTitle() == class_titles[j]) {
				// same class has multiple course objects.
				// sum up the total time and store in every object of that class.
				count_time += classes[i].getDurationMinuteTotal();
			}
		}
		times.push_back(count_time);
	}

	// set member variables.
	for (int i = 0; i < classes.size(); i++) {
		for (int j = 0; j < class_titles.size(); j++) {
			if (classes[i].getCourseTitle() == class_titles[j]) {
				classes[i].setDurationTotal(times[j]);
			}
		}
	}

}
bool classSort_custom(const course& class1, const course& class2) {
	if (class1.getDurationMinuteTotal() > class2.getDurationMinuteTotal()) {
		return true;
	} else if (class1.getDurationMinuteTotal() == class2.getDurationMinuteTotal()) {
		return class1.getCourseTitle() < class2.getCourseTitle();
	}
	return false;
}

void printClasses(ofstream& outputFile, vector<course>& classes, \
	string mode, string deptCode) {
	// this function contains the entire outputting operation.
	if (mode == "custom") {
		int c = 0;
		string tmp = "";
		calculations(classes);
		sort(classes.begin(), classes.end(), classSort_custom);
		outputFile << "Ranking for class time: "  << endl << endl;
		for (int i = 0; i < classes.size(); i++) {
			if (tmp != classes[i].getCourseTitle()) {
				c++;
				outputFile << c << ": " << classes[i].getCourseTitle();
				outputFile << endl << " ==>" << classes[i].getDurationMinuteTotal() / 60 << " hour(s) and ";
				outputFile << classes[i].getDurationMinuteTotal() % 60 << " mintue(s) in weekly total." << endl << endl;
				tmp = classes[i].getCourseTitle();
			}
		}
		return; // function ends here for custom output.
	}
	if (mode == "dept") {
		if (!checkIfDeptExist(classes, deptCode)) {
			outputFile << "No data available." << std::endl;
			return;
		}
	}
	vector<string> columnNames;
	columnNames.push_back("Dept"); columnNames.push_back("Coursenum");
	columnNames.push_back("Class Title"); columnNames.push_back("Day");
	columnNames.push_back("Start Time"); columnNames.push_back("End Time");

	classes = prepare_classes_vector(classes, mode);

	int count = 0;
	if (mode == "room") {
		vector<string> classes_sorted; // sorted classroom names.
		output_room_ordered(classes, classes_sorted);
		vector< vector<int> > widths;
		columnsWidths_room(classes, widths, classes_sorted);

		// printing starts.
		for (int l = 0; l < classes_sorted.size(); l++) {
			count = 0;
			// first 3 lines for each room.
			outputFile << "Room " << classes_sorted[l] << endl;
			for (int k =0; k < 6; k++) {
				outputFile << left << setw(widths[l][k]) << columnNames[k];
				if (k != 5) { outputFile << "  "; }
			}
			outputFile << endl;
			for (int k = 0; k < 6; k++) {
				outputFile << left << setw(widths[l][k]) << string(widths[l][k], '-');
				if (k != 5) { outputFile << "  "; }
			} outputFile << endl;

			// print classes associated with this room.
			for (int i = 0; i < classes.size(); i++) {
				if (classes[i].getRoom() != classes_sorted[l]) { continue; }
				count++;
				for (int j = 0; j < 6; j++) {
					outputFile << left << setw(widths[l][j]) << classes[i].getInfo()[j+1];
					if (j != 5) { outputFile << "  "; }
				} outputFile << endl;
			}

			outputFile << count << " entries" << endl << endl;
		}
	} else {
		vector<int> widths;
		columnsWidths_dept(classes, widths, deptCode);

		// printing starts. first 3 lines.
		outputFile << "Dept " << deptCode << endl;
		for (int k = 1; k < 6; k++) {
			outputFile << left << setw(widths[k]) << columnNames[k];
			if (k != 5) { outputFile << "  "; }
		} outputFile << endl;
		for (int k = 1; k < 6; k++) {
			outputFile << left << setw(widths[k]) << string(widths[k], '-');
			if (k != 5) { outputFile << "  "; }
		} outputFile << endl;
		// start printing classes info.
		for (int i = 0; i < classes.size(); i++) {
			if (classes[i].getDeptCode() == deptCode) {
				count++;
				for (int j = 1; j < 6; j++) {
					outputFile << left << setw(widths[j]) << classes[i].getInfo()[j+1];
					if (j != 5) { outputFile << "  "; }
				} outputFile << endl;
			}
		}
		outputFile << count << " entries" << endl << endl;
	}
}
