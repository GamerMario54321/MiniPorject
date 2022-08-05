#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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
	int chess = 0, dancing = 0, gaming = 0, running = 0, swimming = 0, tenis = 0;
	char special = 'n';

	void init();
};	