#pragma once
#include <string>
#include <vector>
using namespace std;

class student {
public:
	student();
	string getStudentName();
	vector<char> getStudentChoice();
	vector<bool> getStudnetSsport();
	double getStudentGPA();
	void setStudentName(string);
	void setStudentChoice(char, char, char);
	void setStudnetSsport(bool, bool, bool);
	void setStudentGPA(double);
	double combined;
	bool stole;
	string stolen;

private:
	string name;
	vector<char> choice;
	vector<bool> Ssport;
	double GPA;
};

struct sports{
	int chess = 4;
	int dancing = 4;
	int gaming = 4;
	int running = 8;
	int swimming = 4;
	int tenis = 4;
	char special = 'G';
};	