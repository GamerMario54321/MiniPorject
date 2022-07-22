#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "student_data.h"
using namespace std;

vector<student> read_studentData();
void clrscr();
vector<student> sort(vector<student> data, int num);
vector<vector<student>> round1(vector<student> data, sports spdata);
void round1kick(vector<student>& thing, int kick, vector<student>& kicked);
vector<vector<student>> round2(vector<vector<student>> data, sports spdata);
vector<vector<student>> round3(vector<vector<student>> data, sports spdata);
vector<vector<student>> round4(vector<vector<student>> data, sports spdata);
vector<vector<student>> round5(vector<vector<student>> data, sports spdata);
int random();