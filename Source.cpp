#include <iostream>
#include <string>
#include <vector>
#include "student_data.h"
#include "main_func.h"
using namespace std;

int main() {
	sports spdata;
	vector<student> data1 = read_studentData();
	vector<vector<student>> data2 = round1(data1, spdata);
	vector<vector<student>> data3 = round2(data2, spdata);
	vector<vector<student>> data4 = round3(data3, spdata);
	vector<vector<student>> data5 = round4(data4, spdata);
	vector<vector<student>> data6 = round5(data5, spdata);
	return 0;
}