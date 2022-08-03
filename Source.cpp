#include <iostream>
#include <string>
#include <vector>
#include "student_data.h"
#include "main_func.h"
using namespace std;

int main() {
	vector<student> data1 = read_studentData();
	vector<vector<student>> data2 = round1(data1);
	vector<vector<student>> data3 = round2(data2);
	vector<vector<student>> data4 = round3or4(data3, 1);
	vector<vector<student>> data5 = round3or4(data4, 2);
	vector<vector<student>> data6 = round5(data5);
	write_studentData(data6);
	return 0;
}