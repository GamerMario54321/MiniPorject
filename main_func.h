#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "student_data.h"
using namespace std;

vector<student> read_studentData();
void write_studentData(vector<vector<student>> list);
void writeto(vector<student> list, string sport);

void clrscr();

vector<student> sortVector(vector<student> data, int num, int combined);
int Partition(vector<student>& v, int start, int end);
void Quicksort(vector<student>& v, int start, int end);


void pushVector(vector<vector<student>> data, vector<student> &s1, vector <student> &s2, vector <student> &s3, vector <student> &s4, vector <student> &s5, vector <student> &s6, vector <student> &s7);

vector<vector<student>> round1(vector<student> data);
void round1kick(vector<student>& thing, int kick, vector<student>& kicked);

vector<vector<student>> round2(vector<vector<student>> data);
int round2kick(vector<student> &list, vector<student> &kicked, int size, string name);
void round2steal(vector<student>& list, vector<student>& steal, string name);
void round2erase(vector<student>& list, vector<student>& steal);

vector<vector<student>> round3or4(vector<vector<student>> data, int round);
void round3or4insert(vector<student>& list, vector<student>& list2, vector<student>& kicked, int round, int size);

vector<vector<student>> round5(vector<vector<student>> data);

void roundprint(vector<student> list, string name, int round = 3);


int random();