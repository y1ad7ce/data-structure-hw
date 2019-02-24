#ifndef __COURSE_H
#define __COURSE_H

class course {
public:
	course();
	course(std::string CRN, std::string deptCode, std::string courseCode, \
	std::string courseTitle, std::string Days, std::string timeStarts, \
	std::string timeEnds, std::string Room);

	// Accessors
	std::string getCRN() const { return crn; }
	std::string getDeptCode() const { return dept_code; }
	std::string getCourseCode() const { return course_code; }
	std::string getCourseTitle() const { return course_title; }
	std::string getDays() const { return days; }
	std::string getTimeStarts() const { return time_starts; }
	std::string getTimeEnds() const { return time_ends; }
	std::string getRoom() const { return room; }
	std::vector<std::string> getInfo() const { return info; }

	int getDayNum() const { return dayNum; }
	float getStartTime() const { return startTime; }
  int getDurationMinuteTotal() const { return duration_min_total; }

	// Modifiers
	void setDay(std::string day);
	void setDuration(int duration);
	void setDurationTotal(int d) { duration_min_total = d; }

private:
	// member variables:
	std::string crn;
	std::string dept_code;
	std::string course_code;
	std::string course_title;
	std::string days;
	std::string time_starts;
	std::string time_ends;
	std::string room;
	std::vector<std::string> info;

	// helper member variables for easy sorting:
	int dayNum;
	float startTime, endTime;
	int duration_min_total;
};



bool classSort_room(const course& class1, const course& class2);
bool classSort_dept(const course& class1, const course& class2);
void output_room_ordered(std::vector<course> classes, std::vector<course>& classes_sorted);

std::vector<course> prepare_classes_vector(std::vector<course>& classes, std::string mode);

void columnsWidths_room(std::vector<course>& classes, std::vector< std::vector<int> >& widths, \
	std::vector<std::string>& classes_sorted);
void columnsWidths_dept(std::vector<course>& classes, std::vector<int>& widths, std::string deptName);

bool checkIfDeptExist(std::vector<course>& classes, std::string& deptCode);
// two functions for custom output.
void calculations(std::vector<course>& classes);
bool classSort_custom(const course& class1, const course& class2);

void printClasses(std::ofstream& outputFile, std::vector<course>& classes, \
	std::string mode, std::string deptName);

#endif
