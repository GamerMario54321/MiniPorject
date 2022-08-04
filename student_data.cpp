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

void sports::init() {
	ifstream myFile;
	vector<string> cells;
	string cell, line;

	myFile.open("sports.csv");

	if (myFile.good() != 1) {
		cout << "Fatal error: Could not find sports.csv\n";
		system("pause");
		abort();
	}

	getline(myFile, line);
	//cout << line << endl;				

	for (int i = 0; i < line.size(); i++) {
		if (line.at(i) != ',') {
			cell += line.at(i);
		}
		else {
			cells.push_back(cell);
			cell.clear();
		}
	}
	cells.push_back(cell);
	cell.clear();


	if (cells.at(0).find_first_of("0123456789") == std::string::npos) {
		cout << "Fatal error: sports.csv format not correct!\n";
		system("pause");
		abort();
	}

	if (cells.at(1).find_first_of("0123456789") == std::string::npos) {
		cout << "Fatal error: sports.csv format not correct!\n";
		system("pause");
		abort();
	}

	if (cells.at(2).find_first_of("0123456789") == std::string::npos) {
		cout << "Fatal error: sports.csv format not correct!\n";
		system("pause");
		abort();
	}

	if (cells.at(3).find_first_of("0123456789") == std::string::npos) {
		cout << "Fatal error: sports.csv format not correct!\n";
		system("pause");
		abort();
	}

	if (cells.at(4).find_first_of("0123456789") == std::string::npos) {
		cout << "Fatal error: sports.csv format not correct!\n";
		system("pause");
		abort();
	}

	if (cells.at(5).find_first_of("0123456789") == std::string::npos) {
		cout << "Fatal error: sports.csv format not correct!\n";
		system("pause");
		abort();
	}

	if (cells.at(6).find_first_of("CDGRST") == std::string::npos) {
		cout << "Fatal error: sports.csv format not correct!\n";
		system("pause");
		abort();
	}

	chess = stoi(cells.at(0));
	dancing = stoi(cells.at(1));
	gaming = stoi(cells.at(2));
	running = stoi(cells.at(3));
	swimming = stoi(cells.at(4));
	tenis = stoi(cells.at(5));
	special = cells.at(6).at(0);
}