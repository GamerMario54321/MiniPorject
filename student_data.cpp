#include "student_data.h"
using namespace std;

student::student() {
	name = "default";
	choice = { 'C', 'D', 'G' };
	Ssport = { 0, 0, 0 };
	GPA = 0.0;
}

void student::setStudentName(string s) {
	name = s;
}

void student::setStudentChoice(char c1, char c2, char c3) {
	choice = { c1, c2, c3 };
}

void student::setStudnetSsport(bool i1, bool i2, bool i3) {
	Ssport = { i1, i2, i3 };
}

void student::setStudentGPA(double d) {
	GPA = d;
}

string student::getStudentName() {
	return name;
}

vector<char> student::getStudentChoice() {
	return choice;
}

vector<bool> student::getStudnetSsport() {
	return Ssport;
}

double student::getStudentGPA() {
	return GPA;
}