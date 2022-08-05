#include "main_func.h"
#include "student_data.h"
using namespace std;


vector<student> read_studentData() {
	student temp;			
	ifstream myFile;		
	vector<student> data;	
	vector<string> cells;	
	string linecount, cell;	
	int TotalStudents = 0;	

	myFile.open("student.csv");

	if (myFile.good() != 1) {
		cout << "Fatal error: Could not find student.csv\n";
		system("pause");
		abort();
	}
									
	while (getline(myFile, linecount)) 
		TotalStudents++;			
									
	myFile.close();					

	myFile.open("student.csv");

	while (TotalStudents != 0) {
		string line;																				
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

		//for (int i = 0; i < cells.size(); i++) {
		//	cout << cells.at(i) << "|";
		//}
		//cout << endl;

		if (cells.size() != 8) {								
			cout << "Fatal error: student.csv format not correct!\n";
			system("pause");
			abort();											
		}														
		if (cells.at(1).find_first_of("CDGRST") == string::npos) {
			cout << "Fatal error: choices option not valid\n";
			system("pause");
			abort();											
		}														
		if (cells.at(2).find_first_of("CDGRST") == string::npos) {
			cout << "Fatal error: choices option not valid\n";
			system("pause");
			abort();											
		}														
		if (cells.at(3).find_first_of("CDGRST") == string::npos) {
			cout << "Fatal error: choices option not valid\n";
			system("pause");
			abort();											
		}														
		if (cells.at(4).find_first_of("10") == string::npos) {	
			cout << "Fatal error: won compition history not set to 1 or 0\n";
			system("pause");
			abort();											
		}														
		if (cells.at(5).find_first_of("10") == string::npos) {	
			cout << "Fatal error: won compition history not set to 1 or 0\n";
			system("pause");
			abort();											
		}														
		if (cells.at(6).find_first_of("10") == string::npos) {	
			cout << "Fatal error: won compition history not set to 1 or 0\n";
			system("pause");
			abort();											
		}														
		try														
		{														
			temp.setStudentGPA(stold(cells.at(7)));				
		}														
		catch (exception& e)									
		{					
			system("pause");
			cout << "Fatal error: GPA value not vaild\n";								
			abort();											
		}														

		temp.setStudentName(cells.at(0));												
		temp.setStudnetSsport(stoi(cells.at(4)), stoi(cells.at(5)), stoi(cells.at(6)));	
		temp.setStudentChoice(cells.at(1).at(0), cells.at(2).at(0), cells.at(3).at(0));	
		cells.clear();																	

		data.push_back(temp);															

		TotalStudents--;																
	}
	myFile.close();																		
	return data;																		
}





void write_studentData(vector<vector<student>> list) {
	vector<student> chess, dancing, gaming, running, swimming, tenis, empty;
	vector<student>::iterator it;
	pushVector(list, chess, dancing, gaming, running, swimming, tenis, empty);

	cout << "writing csv files\n";

	writeto(chess, "Chess");
	writeto(dancing, "Dancing");
	writeto(gaming, "Gaming");
	writeto(running, "Running");
	writeto(swimming, "Swimming");
	writeto(tenis, "Tennis");

	cout << "Writing complete\n";
	clrscr();
}



void writeto(vector<student> list, string name) {
	vector<student>::iterator it;
	ofstream fout;
	fout.open(name + ".csv");

	fout << "Name, Choice, GPA\n";

	for (it = list.begin(); it != list.end(); it++) {
		fout << it->getStudentName() << ",";
		if (it->stolen == "random")
			fout << " Random,";
		else if (it->getStudentChoice().at(0) == name.at(0))
			fout << " Choice 1,";
		else if (it->stole == 1)
			fout << " Stolen from " << it->stolen << ",";
		else if (it->getStudentChoice().at(1) == name.at(0))
			fout << " Choice 2,";
		else if (it->getStudentChoice().at(2) == name.at(0))
			fout << " Choice 3,";

		fout << it->getStudentGPA() << "\n";
	}

	fout.close();
}




void clrscr() {
	system("pause");
	cout << "\033[2J\033[1;1H";
}




void pushVector(vector<vector<student>> data, vector<student>& s1, vector <student>& s2, vector <student>& s3, vector <student>& s4, vector <student>& s5, vector <student>& s6, vector <student>& s7) {
	vector<student>::iterator it;
	for (it = data.at(0).begin(); it != data.at(0).end(); it++) {
		s1.push_back(*it);
	}
	for (it = data.at(1).begin(); it != data.at(1).end(); it++) {
		s2.push_back(*it);
	}
	for (it = data.at(2).begin(); it != data.at(2).end(); it++) {
		s3.push_back(*it);
	}
	for (it = data.at(3).begin(); it != data.at(3).end(); it++) {
		s4.push_back(*it);
	}
	for (it = data.at(4).begin(); it != data.at(4).end(); it++) {
		s5.push_back(*it);
	}
	for (it = data.at(5).begin(); it != data.at(5).end(); it++) {
		s6.push_back(*it);
	}
	for (it = data.at(6).begin(); it != data.at(6).end(); it++) {
		s7.push_back(*it);
	}
}





vector<student> sortVector(vector<student> list, int num, int combine) {
	if (list.size() <= 1)
		return list;

	vector<student>::iterator it;
	if (combine == 1) {
		for (it = list.begin(); it != list.end(); it++)
			it->combined = it->getStudnetSsport().at(num) + (it->getStudentGPA() / 10);
	}

	Quicksort(list, 0, list.size()-1);

	return list;
}

int Partition(vector<student>& v, int start, int end) {

	int pivot = end;
	int j = start;
	for (int i = start; i < end; ++i) {
		if (v.at(i).combined > v.at(pivot).combined) {
			swap(v[i], v[j]);
			++j;
		}
	}
	swap(v[j], v[pivot]);
	return j;

}

void Quicksort(vector<student>& v, int start, int end) {

	if (start < end) {
		int p = Partition(v, start, end);
		Quicksort(v, start, p - 1);
		Quicksort(v, p + 1, end);
	}

}


vector<vector<student>> round1(vector<student> data) {
	vector<student> chess, dancing, gaming, running, swimming, tenis, kicked;		
	sports spdata;
	spdata.init();
	vector<student>::iterator it;													
	vector<vector<student>> final;

	for (it = data.begin(); it != data.end(); it++) {								
		switch (it->getStudentChoice().at(0)) {										
		case 'C':																	
			chess.push_back(*it);													
			break;																	
																					
		case 'D':																	
			dancing.push_back(*it);													
			break;																	
																					
		case 'G':																	
			gaming.push_back(*it);													
			break;																	
																					
		case 'R':																	
			running.push_back(*it);													
			break;																	
																					
		case 'S':																	
			swimming.push_back(*it);												
			break;																	
																					
		case 'T':																	
			tenis.push_back(*it);													
			break;																	
		}																			
	}																				

	if (chess.size() > spdata.chess)												
		round1kick(chess, chess.size() - spdata.chess, kicked);						
	if (dancing.size() > spdata.dancing)											
		round1kick(dancing, dancing.size() - spdata.dancing, kicked);				
	if (gaming.size() > spdata.gaming)												
		round1kick(gaming, gaming.size() - spdata.gaming, kicked);					
	if (running.size() > spdata.running)											
		round1kick(running, running.size() - spdata.running, kicked);				
	if (swimming.size() > spdata.swimming)											
		round1kick(swimming, swimming.size() - spdata.swimming, kicked);			
	if (tenis.size() > spdata.tenis)												
		round1kick(tenis, tenis.size() - spdata.tenis, kicked);						

	roundprint(chess, "Chess", -1);
	roundprint(dancing, "Dancing", -1);
	roundprint(gaming, "Gaming", -1);
	roundprint(running, "Running", -1);
	roundprint(swimming, "Swimming", -1);
	roundprint(tenis, "Tennis", -1);
	roundprint(kicked, "Kicked", -1);														

	final.push_back(chess);
	final.push_back(dancing);
	final.push_back(gaming);
	final.push_back(running);
	final.push_back(swimming);
	final.push_back(tenis);
	final.push_back(kicked);

	return final;
}

void round1kick(vector<student>& list, int kick, vector<student>& kicked) {
	list = sortVector(list, 0, 1);

	//for (int i = 0; i < list.size(); i++) {							
	//	cout << list.at(i).getStudentName() << "(" << list.at(i).combined < "); 
	//}																	

	for (kick; kick != 0; kick--) {	
		kicked.push_back(list.back());
		list.pop_back();			
	}								
}




vector<vector<student>> round2(vector<vector<student>> data) {
	vector<student> chess, dancing, gaming, running, swimming, tenis, kicked;
	vector<student> steal;
	vector<vector<student>> final;
	vector<student>::iterator it;
	sports spdata;
	spdata.init();
	int win = 0, kick, free;
	pushVector(data, chess, dancing, gaming, running, swimming, tenis, kicked);
	cout << "round 2\n============================\n";

	switch (spdata.special) {
	case 'C':
		win = round2kick(chess, kicked, spdata.chess, "Chess");
		break;

	case 'D':
		win = round2kick(dancing, kicked, spdata.dancing, "Dancing");
		break;

	case 'G':
		win = round2kick(gaming, kicked, spdata.gaming, "Gaming");
		break;

	case 'R':
		win = round2kick(running, kicked, spdata.running, "Running");
		break;

	case 'S':
		win = round2kick(swimming, kicked, spdata.swimming, "Swimming");
		break;

	case 'T':
		win = round2kick(tenis, kicked, spdata.tenis, "Tennis");
		break;
	}

	if (win < 3) {
		if (spdata.special != 'C')
			round2steal(chess, steal, "Chess");

		if (spdata.special != 'D')
			round2steal(dancing, steal, "Dancing");

		if (spdata.special != 'G')
			round2steal(gaming, steal, "Gaming");

		if (spdata.special != 'R')
			round2steal(running, steal, "Running");

		if (spdata.special != 'S')
			round2steal(swimming, steal, "Swimming");

		if (spdata.special != 'T')
			round2steal(tenis, steal, "Tennis");

		round2steal(kicked, steal, "nothing");

		sortVector(steal, 0, 0);

		for (kick = 3 - win; kick != 0; kick--) {
			switch (spdata.special) {
			case 'C':
				steal.back().stole = true;
				chess.push_back(steal.back());
				break;

			case 'D':
				steal.back().stole = true;
				dancing.push_back(steal.back());
				break;

			case 'G':
				steal.back().stole = true;
				gaming.push_back(steal.back());
				break;

			case 'R':
				steal.back().stole = true;
				running.push_back(steal.back());
				break;

			case 'S':
				steal.back().stole = true;
				swimming.push_back(steal.back());
				break;

			case 'T':
				steal.back().stole = true;
				tenis.push_back(steal.back());
				break;
			}

			cout << steal.back().getStudentName() << " Stolen from " << steal.back().stolen << endl;
			
			switch (steal.back().stolen.at(0)) {
			case 'C':
				round2erase(chess, steal);
				break;

			case 'D':
				round2erase(dancing, steal);
				break;

			case 'G':
				round2erase(gaming, steal);
				break;

			case 'R':
				round2erase(running, steal);
				break;

			case 'S':
				round2erase(swimming, steal);
				break;

			case 'T':
				round2erase(tenis, steal);
				break;

			case 'n':
				round2erase(kicked, steal);
				break;
			}

			steal.pop_back();
		}
	}
	cout << "\n\n";
	clrscr();
	final.push_back(chess);
	final.push_back(dancing);
	final.push_back(gaming);
	final.push_back(running);
	final.push_back(swimming);
	final.push_back(tenis);
	final.push_back(kicked);

	return final;
}


int round2kick(vector<student> &list, vector<student> &kicked, int size, string name) {
	int win = 0, kick, free;
	vector<student>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		if (it->getStudnetSsport().at(0) > 0)
			win++;
	}
	cout << name << " stealing\n\n";
	free = 3 - win;
	for (kick = 3 - win; kick != 0; kick--) {
		if (size - list.size() >= free)
			break;

		kicked.push_back(list.back());
		cout << list.back().getStudentName() << " kicked from " << name << endl;
		list.pop_back();
	}

	return win;
}

void round2steal(vector<student> &list, vector<student> &steal, string name) {
	vector<student>::iterator it;
	sports spdata;
	spdata.init();
	for (it = list.begin(); it != list.end(); it++) {
		if (it->getStudentChoice().at(1) == spdata.special && it->getStudnetSsport().at(1) > 0) {
			it->stolen = name;
			it->combined = it->getStudnetSsport().at(1) + (it->getStudentGPA() / 10);
			steal.push_back(*it);
		}
		if (it->getStudentChoice().at(2) == spdata.special && it->getStudnetSsport().at(2) > 0) {
			it->stolen = name;
			it->combined = it->getStudnetSsport().at(2) + (it->getStudentGPA() / 10);
			steal.push_back(*it);
		}
	}
}

void round2erase(vector<student> &list, vector<student> &steal) {
	vector<student>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		if (steal.back().getStudentName() == it->getStudentName()) {
			list.erase(it);
			break;
		}
	}
}



vector<vector<student>> round3or4(vector<vector<student>> data, int round) {
	vector<student> chess, dancing, gaming, running, swimming, tenis, kicked;
	vector<student> chess2, dancing2, gaming2, running2, swimming2, tenis2;
	vector<student>::iterator it;
	vector<vector<student>> final;
	sports spdata;
	spdata.init();
	pushVector(data, chess, dancing, gaming, running, swimming, tenis, kicked);

	for (it = kicked.begin(); it != kicked.end(); it++) {
		switch (it->getStudentChoice().at(round)) {
		case 'C':
			chess2.push_back(*it);
			break;

		case 'D':
			dancing2.push_back(*it);
			break;

		case 'G':
			gaming2.push_back(*it);
			break;

		case 'R':
			running2.push_back(*it);
			break;

		case 'S':
			swimming2.push_back(*it);
			break;

		case 'T':
			tenis2.push_back(*it);
			break;
		}
	}

	kicked.clear();

	round3or4insert(chess, chess2, kicked, round, spdata.chess);
	round3or4insert(dancing, dancing2, kicked, round, spdata.dancing);
	round3or4insert(gaming, gaming2, kicked, round, spdata.gaming);
	round3or4insert(running, running2, kicked, round, spdata.running);
	round3or4insert(swimming, swimming2, kicked, round, spdata.swimming);
	round3or4insert(tenis, tenis2, kicked, round, spdata.tenis);


	roundprint(chess, "Chess", round);
	roundprint(dancing, "Dancing", round);
	roundprint(gaming, "Gaming", round);
	roundprint(running, "Running", round);
	roundprint(swimming, "Swimming", round);
	roundprint(tenis, "Tennis", round);
	roundprint(kicked, "Kicked", round);

	final.push_back(chess);
	final.push_back(dancing);
	final.push_back(gaming);
	final.push_back(running);
	final.push_back(swimming);
	final.push_back(tenis);
	final.push_back(kicked);

	return final;
}

void round3or4insert(vector<student> &list, vector<student> &list2, vector<student> &kicked, int round, int size) {
	vector<student>::iterator it;
	if (size - list.size() > 0) {
		sortVector(list2, round, 0);
		for (int i = size - list.size(); i != 0; i--) {
			if (list2.size() != 0) {
				list.push_back(list2.back());
				list2.pop_back();
			}
			else
				break;
		}
	}
	if (list2.size() != 0) {
		for (it = list2.begin(); it != list2.end(); it++)
			kicked.push_back(*it);
	}
}


vector<vector<student>> round5(vector<vector<student>> data) {
	vector<student> chess, dancing, gaming, running, swimming, tenis, kicked;
	vector<student>::iterator it;
	vector<vector<student>> final;
	sports spdata;
	spdata.init();
	pushVector(data, chess, dancing, gaming, running, swimming, tenis, kicked);

	srand(time(0));
	for (it = kicked.begin(); it != kicked.end(); it++) {
	bool b = 1;
		it->stolen = "random";
		do {
			int thing = random();
			switch (thing) {
			case 1:
				if (chess.size() < spdata.chess) {
					chess.push_back(*it);
					b = 0;
				}
				break;

			case '2':
				if (dancing.size() < spdata.dancing) {
					dancing.push_back(*it);
					b = 0;
				}
				break;

			case '3':
				if (gaming.size() < spdata.gaming) {
					gaming.push_back(*it);
					b = 0;
				}
				break;

			case '4':
				if (running.size() < spdata.running) {
					running.push_back(*it);
					b = 0;
				}
				break;

			case '5':
				if (swimming.size() < spdata.swimming) {
					swimming.push_back(*it);
					b = 0;
				}
				break;

			case '6':
				if (tenis.size() < spdata.tenis) {
					tenis.push_back(*it);
					b = 0;
				}
				break;
			}
		} while (b != 0);
	}

	roundprint(chess, "Chess");
	roundprint(dancing, "Dancing");
	roundprint(gaming, "Gaming");
	roundprint(running, "Running");
	roundprint(swimming, "Swimming");
	roundprint(tenis, "Tennis");

	final.push_back(chess);
	final.push_back(dancing);
	final.push_back(gaming);
	final.push_back(running);
	final.push_back(swimming);
	final.push_back(tenis);
	final.push_back(kicked);

	return final;
}


void roundprint(vector<student> list, string name, int round) {
	vector<student>::iterator it;
	cout << "round " << round + 2 << "\n============================\n" << name << "\n\n";
	for (it = list.begin(); it != list.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->stolen == "random")
			cout << " Random\n";
		else if (name == "Kicked")
			cout << "\n";
		else if (it->getStudentChoice().at(0) == name.at(0))
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == name.at(0))
			cout << " Choice 2\n";
		else if (it->getStudentChoice().at(2) == name.at(0))
			cout << " Choice 3\n";
	}
	cout << "\n\n";
	clrscr();
}


int random() {
	for (int i = 0; i < 3; i++)
		return rand() % 6 + 1;
}