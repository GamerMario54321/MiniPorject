#include "main_func.h"
#include "student_data.h"
using namespace std;

vector<student> read_studentData() {
	student temp;																				//
	ifstream myFile;																			//
	vector<student> data;																		// Declaring Varribles
	vector<string> cells;																		//
	string linecount, cell;																		//
	int TotalStudents = 0;																		//

	myFile.open("student.csv");

	if (myFile.good() != 1) {
		cout << "Fatal error: Could not find student.csv";
		system("pause");
		abort();
	}
																								//
	while (getline(myFile, linecount)) 															// Line counter
		TotalStudents++;																		//
																								//
	myFile.close();																				//

	myFile.open("student.csv");

	while (TotalStudents != 0) {
		string line;																			//
		getline(myFile, line);																	//
		//cout << line << endl;																	//
																								//
		for (int i = 0; i < line.size(); i++) {													//
			if (line.at(i) != ',') {															//
				cell += line.at(i);																// Putting each cell from one row into a string varaible
			}																					//
			else {																				//
				cells.push_back(cell);															//
				cell.clear();																	//
			}																					//
		}																						//
		cells.push_back(cell);																	//
		cell.clear();																			//

		//for (int i = 0; i < cells.size(); i++) {
		//	cout << cells.at(i) << "|";
		//}
		//cout << endl;

		if (cells.size() != 8) {								
			cout << "Fatal error: student.csv format not correct!";
			system("pause");
			abort();											
		}														
		if (cells.at(1).find_first_of("CDGRST") == string::npos) {
			cout << "Fatal error: choices option not valid";
			system("pause");
			abort();											
		}														
		if (cells.at(2).find_first_of("CDGRST") == string::npos) {
			cout << "Fatal error: choices option not valid";
			system("pause");
			abort();											
		}														
		if (cells.at(3).find_first_of("CDGRST") == string::npos) {
			cout << "Fatal error: choices option not valid";
			system("pause");
			abort();											
		}														
		if (cells.at(4).find_first_of("10") == string::npos) {	
			cout << "Fatal error: won compition history not set to 1 or 0";
			system("pause");
			abort();											
		}														
		if (cells.at(5).find_first_of("10") == string::npos) {	
			cout << "Fatal error: won compition history not set to 1 or 0";
			system("pause");
			abort();											
		}														
		if (cells.at(6).find_first_of("10") == string::npos) {	
			cout << "Fatal error: won compition history not set to 1 or 0";
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
			cout << "Fatal error: GPA value not vaild";								
			abort();											
		}														

		temp.setStudentName(cells.at(0));														//
		temp.setStudnetSsport(stoi(cells.at(4)), stoi(cells.at(5)), stoi(cells.at(6)));			// seting the temp student class from the varaibles from the cell										
		temp.setStudentChoice(cells.at(1).at(0), cells.at(2).at(0), cells.at(3).at(0));			// then clearing the cells for the next row
		cells.clear();																			// 

		data.push_back(temp);																	// pushing the temp student class into the vector student class

		TotalStudents--;																		// for line count purposes
	}
	myFile.close();																				// closing the file
	return data;																				// returning the data
}







void clrscr() {
	system("pause");
	cout << "\033[2J\033[1;1H";
}






vector<student> sort(vector<student> list, int num) {
	if (list.size() <= 1)
		return list;

	vector<student>::iterator it;
	for (it = list.begin(); it != list.end(); it++)												// combining the history of won competition and gpa into a double by:
		it->combined = it->getStudnetSsport().at(num) + (it->getStudentGPA() / 10);				// won.gpa

	for (int i = 0; i < list.size() - 1; i++) {													//
		for (int o = 0; o < list.size() - i - 1; o++) {											// bubble sort
			if (list.at(o).combined < list.at(o + 1).combined)									//
				swap(list.at(o), list.at(o + 1));												//
		}																						//
	}

	return list;
}




vector<vector<student>> round1(vector<student> data, sports spdata) {
	vector<student> chess, dancing, gaming, running, swimming, tenis, kicked;					// vector declaration
	vector<student>::iterator it;																// vector iterator
	vector<vector<student>> final;

	for (it = data.begin(); it != data.end(); it++) {											//
		switch (it->getStudentChoice().at(0)) {													//
		case 'C':																				//
			chess.push_back(*it);																//
			break;																				//
																								//
		case 'D':																				//
			dancing.push_back(*it);																//
			break;																				//
																								//
		case 'G':																				//
			gaming.push_back(*it);																// Pushing back the list of the student first choice into the
			break;																				// other vector classes
																								//
		case 'R':																				//
			running.push_back(*it);																//
			break;																				//
																								//
		case 'S':																				//
			swimming.push_back(*it);															//
			break;																				//
																								//
		case 'T':																				//
			tenis.push_back(*it);																//
			break;																				//
		}																						//
	}																							//

	if (chess.size() > spdata.chess)															//
		round1kick(chess, chess.size() - spdata.chess, kicked);									//
	if (dancing.size() > spdata.dancing)														//
		round1kick(dancing, dancing.size() - spdata.dancing, kicked);							//
	if (gaming.size() > spdata.gaming)															//
		round1kick(gaming, gaming.size() - spdata.gaming, kicked);								// Checking if the the amount of student in their first choice
	if (running.size() > spdata.running)														// exceeds the amount of vacancies in the sport
		round1kick(running, running.size() - spdata.running, kicked);							//
	if (swimming.size() > spdata.swimming)														//
		round1kick(swimming, swimming.size() - spdata.swimming, kicked);						//
	if (tenis.size() > spdata.tenis)															//
		round1kick(tenis, tenis.size() - spdata.tenis, kicked);									//

	cout << "round 1\n============================\nChess\n\n";									//
	for (it = chess.begin(); it != chess.end(); it++)											//
		cout << it->getStudentName() << " " << it->getStudentGPA() << " Choice 1\n";			//
	cout << "\n\n";																				//
	clrscr();																					//
	cout << "round 1\n============================\nDancing\n\n";								//
	for (it = dancing.begin(); it != dancing.end(); it++)										//
		cout << it->getStudentName() << " " << it->getStudentGPA() << " Choice 1\n";			//
	cout << "\n\n";																				//
	clrscr();																					//
	cout << "round 1\n============================\nGaming\n\n";								//
	for (it = gaming.begin(); it != gaming.end(); it++)											// Displaying the results of round 1
		cout << it->getStudentName() << " " << it->getStudentGPA() << " Choice 1\n";			//
	cout << "\n\n";																				//
	clrscr();																					//
	cout << "round 1\n============================\nRunning\n\n";								//
	for (it = running.begin(); it != running.end(); it++)										//
		cout << it->getStudentName() << " " << it->getStudentGPA() << " Choice 1\n";			//
	cout << "\n\n";																				//
	clrscr();																					//
	cout << "round 1\n============================\nSwimming\n\n";								//
	for (it = swimming.begin(); it != swimming.end(); it++)										//
		cout << it->getStudentName() << " " << it->getStudentGPA() << " Choice 1\n";			//
	cout << "\n\n";																				//
	clrscr();																					//
	cout << "round 1\n============================\nTennis\n\n";								//
	for (it = tenis.begin(); it != tenis.end(); it++)											//
		cout << it->getStudentName() << " " << it->getStudentGPA() << " Choice 1\n";			//
	cout << "\n\n";																				//
	clrscr();																					//
	cout << "round 1\n============================\nKicked\n\n";								//
	for (it = kicked.begin(); it != kicked.end(); it++)											//
		cout << it->getStudentName() << " " << it->getStudentGPA() << "\n";						//
	cout << "\n\n";																				//
	clrscr();																					//

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
	list = sort(list, 0);

	//for (int i = 0; i < list.size(); i++) {													  //
	//	cout << list.at(i).getStudentName() << "(" << list.at(i).combined << ")";				  // print out sorted list for checking purposes
	//}																							  // remove "//" if needed

	for (kick; kick != 0; kick--) {																//
		kicked.push_back(list.back());															// kicking by adding the kick people to the kicked vector
		list.pop_back();																		// and pop_back the back of the original list
	}																							//
}









vector<vector<student>> round2(vector<vector<student>> data, sports spdata) {
	vector<student> chess, dancing, gaming, running, swimming, tenis, kicked;
	vector<student> steal;
	vector<vector<student>> final;
	vector<student>::iterator it;
	cout << "round 2\n============================\n";
	int win = 0, kick, free;
	for (int i = 0; i < data.at(0).size(); i++) {
		chess.push_back(data.at(0).at(i));
	}
	for (int i = 0; i < data.at(1).size(); i++) {
		dancing.push_back(data.at(1).at(i));
	}
	for (int i = 0; i < data.at(2).size(); i++) {
		gaming.push_back(data.at(2).at(i));
	}
	for (int i = 0; i < data.at(3).size(); i++) {
		running.push_back(data.at(3).at(i));
	}
	for (int i = 0; i < data.at(4).size(); i++) {
		swimming.push_back(data.at(4).at(i));
	}
	for (int i = 0; i < data.at(5).size(); i++) {
		tenis.push_back(data.at(5).at(i));
	}
	for (int i = 0; i < data.at(6).size(); i++) {
		kicked.push_back(data.at(6).at(i));
	}

	switch (spdata.special) {
	case 'C':
		for (it = chess.begin(); it != chess.end(); it++) {
			if (it->getStudnetSsport().at(0) > 0)
				win++;
		}
		cout << "Chess stealing\n\n";
		free = 3 - win;
		for (kick = 3 - win; kick != 0; kick--) {
			if (spdata.chess - chess.size() >= free)
				break;
			kicked.push_back(chess.back());
			cout << chess.back().getStudentName() << " kicked from Chess" << endl;
			chess.pop_back();
		}
		break;

	case 'D':
		for (it = dancing.begin(); it != dancing.end(); it++) {
			if (it->getStudnetSsport().at(0) > 0)
				win++;
		}
		cout << "Dancing stealing\n\n";
		free = 3 - win;
		for (kick = 3 - win; kick != 0; kick--) {
			if (spdata.dancing - dancing.size() >= free)
				break;
			kicked.push_back(dancing.back());
			cout << dancing.back().getStudentName() << " kicked from Dancing" << endl;
			dancing.pop_back();
		}
		break;

	case 'G':
		for (it = gaming.begin(); it != gaming.end(); it++) {
			if (it->getStudnetSsport().at(0) > 0)
				win++;
		}
		cout << "Gaming stealing\n\n";
		free = 3 - win;
		for (kick = 3 - win; kick != 0; kick--) {
			if (spdata.gaming - gaming.size() >= free)
				break;
			kicked.push_back(gaming.back());
			cout << gaming.back().getStudentName() << " kicked from Gaming" << endl;
			gaming.pop_back();
		}
		break;

	case 'R':
		for (it = running.begin(); it != running.end(); it++) {
			if (it->getStudnetSsport().at(0) > 0)
				win++;
		}
		cout << "Running stealing\n\n";
		free = 3 - win;
		for (kick = 3 - win; kick != 0; kick--) {
			if (spdata.running - running.size() >= free)
				break;
			kicked.push_back(running.back());
			cout << running.back().getStudentName() << " kicked from Running" << endl;
			running.pop_back();
		}
		break;

	case 'S':
		for (it = swimming.begin(); it != swimming.end(); it++) {
			if (it->getStudnetSsport().at(0) > 0)
				win++;
		}
		cout << "Swimming stealing\n\n";
		free = 3 - win;
		for (kick = 3 - win; kick != 0; kick--) {
			if (spdata.swimming - swimming.size() >= free)
				break;
			kicked.push_back(swimming.back());
			cout << swimming.back().getStudentName() << " kicked from Swimming" << endl;
			swimming.pop_back();
		}
		break;

	case 'T':
		for (it = tenis.begin(); it != tenis.end(); it++) {
			if (it->getStudnetSsport().at(0) > 0)
				win++;
		}
		cout << "Tennis stealing\n\n";
		free = 3 - win;
		for (kick = 3 - win; kick != 0; kick--) {
			if (spdata.tenis - tenis.size() >= free)
				break;
			kicked.push_back(tenis.back());
			cout << tenis.back().getStudentName() << " kicked from Tennis" << endl;
			tenis.pop_back();
		}
		break;
	}

	if (win < 3) {
		if (spdata.special != 'C') {
			for (it = chess.begin(); it != chess.end(); it++) {
				if (it->getStudentChoice().at(1) == spdata.special && it->getStudnetSsport().at(1) > 0) {
					it->stolen = "Chess";
					it->combined = it->getStudnetSsport().at(1) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
				if (it->getStudentChoice().at(2) == spdata.special && it->getStudnetSsport().at(2) > 0) {
					it->stolen = "Chess";
					it->combined = it->getStudnetSsport().at(2) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
			}
		}

		if (spdata.special != 'D') {
			for (it = dancing.begin(); it != dancing.end(); it++) {
				if (it->getStudentChoice().at(1) == spdata.special && it->getStudnetSsport().at(1) > 0) {
					it->stolen = "Dancing";
					it->combined = it->getStudnetSsport().at(1) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
				if (it->getStudentChoice().at(2) == spdata.special && it->getStudnetSsport().at(2) > 0) {
					it->stolen = "Dancing";
					it->combined = it->getStudnetSsport().at(2) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
			}
		}

		if (spdata.special != 'G') {
			for (it = gaming.begin(); it != gaming.end(); it++) {
				if (it->getStudentChoice().at(1) == spdata.special && it->getStudnetSsport().at(1) > 0) {
					it->stolen = "Gaming";
					it->combined = it->getStudnetSsport().at(1) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
				if (it->getStudentChoice().at(2) == spdata.special && it->getStudnetSsport().at(2) > 0) {
					it->stolen = "Gaming";
					it->combined = it->getStudnetSsport().at(2) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
			}
		}

		if (spdata.special != 'R') {
			for (it = running.begin(); it != running.end(); it++) {
				if (it->getStudentChoice().at(1) == spdata.special && it->getStudnetSsport().at(1) > 0) {
					it->stolen = "Running";
					it->combined = it->getStudnetSsport().at(1) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
				if (it->getStudentChoice().at(2) == spdata.special && it->getStudnetSsport().at(2) > 0) {
					it->stolen = "Running";
					it->combined = it->getStudnetSsport().at(2) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
			}
		}

		if (spdata.special != 'S') {
			for (it = swimming.begin(); it != swimming.end(); it++) {
				if (it->getStudentChoice().at(1) == spdata.special && it->getStudnetSsport().at(1) > 0) {
					it->stolen = "Swimming";
					it->combined = it->getStudnetSsport().at(1) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
				if (it->getStudentChoice().at(2) == spdata.special && it->getStudnetSsport().at(2) > 0) {
					it->stolen = "Swimming";
					it->combined = it->getStudnetSsport().at(2) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
			}
		}

		if (spdata.special != 'T') {
			for (it = tenis.begin(); it != tenis.end(); it++) {
				if (it->getStudentChoice().at(1) == spdata.special && it->getStudnetSsport().at(1) > 0) {
					it->stolen = "Tennis";
					it->combined = it->getStudnetSsport().at(1) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
				if (it->getStudentChoice().at(2) == spdata.special && it->getStudnetSsport().at(2) > 0) {
					it->stolen = "Tennis";
					it->combined = it->getStudnetSsport().at(2) + (it->getStudentGPA() / 10);
					steal.push_back(*it);
				}
			}
		}

		for (it = kicked.begin(); it != kicked.end(); it++) {
			if (it->getStudentChoice().at(1) == spdata.special && it->getStudnetSsport().at(1) > 0) {
				it->stolen = "nothing";
				it->combined = it->getStudnetSsport().at(1) + (it->getStudentGPA() / 10);
				steal.push_back(*it);
			}
			if (it->getStudentChoice().at(2) == spdata.special && it->getStudnetSsport().at(2) > 0) {
				it->stolen = "nothing";
				it->combined = it->getStudnetSsport().at(2) + (it->getStudentGPA() / 10);
				steal.push_back(*it);
			}
		}
		for (int i = 0; i < steal.size() - 1; i++) {
			for (int o = 0; o < steal.size() - i - 1; o++) {
				if (steal.at(o).combined > steal.at(o + 1).combined)
					swap(steal.at(o), steal.at(o + 1));
			}
		}

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
				for (it = chess.begin(); it != chess.end(); it++) {
					if (steal.back().getStudentName() == it->getStudentName()) {
						chess.erase(it);
						break;
					}
				}
				break;

			case 'D':
				for (it = dancing.begin(); it != dancing.end(); it++) {
					if (steal.back().getStudentName() == it->getStudentName()) {
						dancing.erase(it);
						break;
					}
				}
				break;

			case 'G':
				for (it = gaming.begin(); it != gaming.end(); it++) {
					if (steal.back().getStudentName() == it->getStudentName()) {
						gaming.erase(it);
						break;
					}
				}
				break;

			case 'R':
				for (it = running.begin(); it != running.end(); it++) {
					if (steal.back().getStudentName() == it->getStudentName()) {
						running.erase(it);
						break;
					}
				}
				break;

			case 'S':
				for (it = swimming.begin(); it != swimming.end(); it++) {
					if (steal.back().getStudentName() == it->getStudentName()) {
						swimming.erase(it);
						break;
					}
				}
				break;

			case 'T':
				for (it = tenis.begin(); it != tenis.end(); it++) {
					if (steal.back().getStudentName() == it->getStudentName()) {
						tenis.erase(it);
						break;
					}
				}
				break;

			case 'n':
				for (it = kicked.begin(); it != kicked.end(); it++) {
					if (steal.back().getStudentName() == it->getStudentName()) {
						kicked.erase(it);
						break;
					}
				}
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




vector<vector<student>> round3(vector<vector<student>> data, sports spdata) {
	vector<student> chess, dancing, gaming, running, swimming, tenis, kicked;
	vector<student> chess2, dancing2, gaming2, running2, swimming2, tenis2;
	vector<student>::iterator it;
	vector<vector<student>> final;
	for (int i = 0; i < data.at(0).size(); i++) {
		chess.push_back(data.at(0).at(i));
	}
	for (int i = 0; i < data.at(1).size(); i++) {
		dancing.push_back(data.at(1).at(i));
	}
	for (int i = 0; i < data.at(2).size(); i++) {
		gaming.push_back(data.at(2).at(i));
	}
	for (int i = 0; i < data.at(3).size(); i++) {
		running.push_back(data.at(3).at(i));
	}
	for (int i = 0; i < data.at(4).size(); i++) {
		swimming.push_back(data.at(4).at(i));
	}
	for (int i = 0; i < data.at(5).size(); i++) {
		tenis.push_back(data.at(5).at(i));
	}
	for (int i = 0; i < data.at(6).size(); i++) {
		kicked.push_back(data.at(6).at(i));
	}

	for (it = kicked.begin(); it != kicked.end(); it++) {
		switch (it->getStudentChoice().at(1)) {
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

	if (spdata.chess - chess.size() > 0) {
		sort(chess2, 1);
		for (int i = spdata.chess - chess.size(); i != 0; i--) {
			if (chess2.size() != 0) {
				chess.push_back(chess2.back());
				chess2.pop_back();
			}
			else
				break;
		}
	}
	if (chess2.size() != 0) {
		for (it = chess2.begin(); it != chess2.end(); it++)
			kicked.push_back(*it);
	}

	if (spdata.dancing - dancing.size() > 0) {
		sort(dancing2, 1);
		for (int i = spdata.dancing - dancing.size(); i != 0; i--) {
			if (dancing2.size() != 0) {
				dancing.push_back(dancing2.back());
				dancing2.pop_back();
			}
		}
	}
	if (dancing2.size() != 0) {
		for (it = dancing2.begin(); it != dancing2.end(); it++)
			kicked.push_back(*it);
	}

	if (spdata.gaming - gaming.size() > 0) {
		sort(gaming2, 1);
		for (int i = spdata.gaming - gaming.size(); i != 0; i--) {
			if (gaming2.size() != 0) {
				gaming.push_back(gaming2.back());
				gaming2.pop_back();
			}
			else
				break;
		}
	}
	if (gaming2.size() > 0) {
		for (it = gaming2.begin(); it != gaming2.end(); it++)
			kicked.push_back(*it);
	}

	if (spdata.running - running.size() > 0) {
		sort(running2, 1);
		for (int i = spdata.running - running.size(); i != 0; --i) {
			if (running2.size() != 0) {
				running.push_back(running2.back());
				running2.pop_back();
			}
			else
				break;
		}
	}
	if (running2.size() > 0) {
		for (it = running2.begin(); it != running2.end(); it++)
			kicked.push_back(*it);
	}

	if (spdata.swimming - swimming.size() > 0) {
		sort(swimming2, 1);
		for (int i = spdata.swimming - swimming.size(); i != 0; i--) {
			if (swimming2.size() != 0) {
				swimming.push_back(swimming2.back());
				swimming2.pop_back();
			}
			else
				break;
		}
	}
	if (swimming2.size() != 0) {
		for (it = swimming2.begin(); it != swimming2.end(); it++)
			kicked.push_back(*it);
	}

	if (spdata.tenis - tenis.size() > 0) {
		sort(tenis2, 1);
		for (int i = spdata.tenis - tenis.size(); i != 0; i--) {
			if (tenis2.size() != 0) {
				tenis.push_back(tenis2.back());
				tenis2.pop_back();
			}
			else
				break;
		}
	}
	if (tenis2.size() != 0) {
		for (it = tenis2.begin(); it != tenis2.end(); it++)
			kicked.push_back(*it);
	}


	cout << "round 3\n============================\nChess\n\n";
	for (it = chess.begin(); it != chess.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'C')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else
			cout << " Choice 2\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 3\n============================\nDancing\n\n";
	for (it = dancing.begin(); it != dancing.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'D')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else
			cout << " Choice 2\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 3\n============================\nGaming\n\n";
	for (it = gaming.begin(); it != gaming.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'G')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else
			cout << " Choice 2\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 3\n============================\nRunning\n\n";
	for (it = running.begin(); it != running.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'R')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else
			cout << " Choice 2\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 3\n============================\nSwimming\n\n";
	for (it = swimming.begin(); it != swimming.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'S')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else
			cout << " Choice 2\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 3\n============================\nTennis\n\n";
	for (it = tenis.begin(); it != tenis.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'T')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else
			cout << " Choice 2\n";
	}
	cout << "\n\n";																	
	clrscr();

	cout << "round 3\n============================\nKicked\n\n";						
	for (it = kicked.begin(); it != kicked.end(); it++)								
		cout << it->getStudentName() << " " << it->getStudentGPA() << "\n";			
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

vector<vector<student>> round4(vector<vector<student>> data, sports spdata) {
	vector<student> chess, dancing, gaming, running, swimming, tenis, kicked;
	vector<student> chess2, dancing2, gaming2, running2, swimming2, tenis2;
	vector<student>::iterator it;
	vector<vector<student>> final;
	for (int i = 0; i < data.at(0).size(); i++) {
		chess.push_back(data.at(0).at(i));
	}
	for (int i = 0; i < data.at(1).size(); i++) {
		dancing.push_back(data.at(1).at(i));
	}
	for (int i = 0; i < data.at(2).size(); i++) {
		gaming.push_back(data.at(2).at(i));
	}
	for (int i = 0; i < data.at(3).size(); i++) {
		running.push_back(data.at(3).at(i));
	}
	for (int i = 0; i < data.at(4).size(); i++) {
		swimming.push_back(data.at(4).at(i));
	}
	for (int i = 0; i < data.at(5).size(); i++) {
		tenis.push_back(data.at(5).at(i));
	}
	for (int i = 0; i < data.at(6).size(); i++) {
		kicked.push_back(data.at(6).at(i));
	}

	for (it = kicked.begin(); it != kicked.end(); it++) {
		switch (it->getStudentChoice().at(2)) {
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

	if (spdata.chess - chess.size() > 0) {
		sort(chess2, 2);
		for (int i = spdata.chess - chess.size(); i != 0; i--) {
			if (chess2.size() != 0) {
				chess.push_back(chess2.back());
				chess2.pop_back();
			}
			else
				break;
		}
	}
	if (chess2.size() != 0) {
		for (it = chess2.begin(); it != chess2.end(); it++)
			kicked.push_back(*it);
	}

	if (spdata.dancing - dancing.size() > 0) {
		sort(dancing2, 2);
		for (int i = spdata.dancing - dancing.size(); i != 0; i--) {
			if (dancing2.size() != 0) {
				dancing.push_back(dancing2.back());
				dancing2.pop_back();
			}
		}
	}
	if (dancing2.size() != 0) {
		for (it = dancing2.begin(); it != dancing2.end(); it++)
			kicked.push_back(*it);
	}

	if (spdata.gaming - gaming.size() > 0) {
		sort(gaming2, 2);
		for (int i = spdata.gaming - gaming.size(); i != 0; i--) {
			if (gaming2.size() != 0) {
				gaming.push_back(gaming2.back());
				gaming2.pop_back();
			}
			else
				break;
		}
	}
	if (gaming2.size() > 0) {
		for (it = gaming2.begin(); it != gaming2.end(); it++)
			kicked.push_back(*it);
	}

	if (spdata.running - running.size() > 0) {
		sort(running2, 2);
		for (int i = spdata.running - running.size(); i != 0; --i) {
			if (running2.size() != 0) {
				running.push_back(running2.back());
				running2.pop_back();
			}
			else
				break;
		}
	}
	if (running2.size() > 0) {
		for (it = running2.begin(); it != running2.end(); it++)
			kicked.push_back(*it);
	}

	if (spdata.swimming - swimming.size() > 0) {
		sort(swimming2, 2);
		for (int i = spdata.swimming - swimming.size(); i != 0; i--) {
			if (swimming2.size() != 0) {
				swimming.push_back(swimming2.back());
				swimming2.pop_back();
			}
			else
				break;
		}
	}
	if (swimming2.size() != 0) {
		for (it = swimming2.begin(); it != swimming2.end(); it++)
			kicked.push_back(*it);
	}

	if (spdata.tenis - tenis.size() > 0) {
		sort(tenis2, 2);
		for (int i = spdata.tenis - tenis.size(); i != 0; i--) {
			if (tenis2.size() != 0) {
				tenis.push_back(tenis2.back());
				tenis2.pop_back();
			}
			else
				break;
		}
	}
	if (tenis2.size() != 0) {
		for (it = tenis2.begin(); it != tenis2.end(); it++)
			kicked.push_back(*it);
	}


	cout << "round 4\n============================\nChess\n\n";
	for (it = chess.begin(); it != chess.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'C')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'C')
			cout << " Choice 2\n";
		else
			cout << " Choice 3\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 4\n============================\nDancing\n\n";
	for (it = dancing.begin(); it != dancing.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'D')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'D')
			cout << " Choice 2\n";
		else
			cout << " Choice 3\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 4\n============================\nGaming\n\n";
	for (it = gaming.begin(); it != gaming.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'G')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'G')
			cout << " Choice 2\n";
		else
			cout << " Choice 3\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 4\n============================\nRunning\n\n";
	for (it = running.begin(); it != running.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'R')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'R')
			cout << " Choice 2\n";
		else
			cout << " Choice 3\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 4\n============================\nSwimming\n\n";
	for (it = swimming.begin(); it != swimming.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'S')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'S')
			cout << " Choice 2\n";
		else
			cout << " Choice 3\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 4\n============================\nTennis\n\n";
	for (it = tenis.begin(); it != tenis.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'T')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'T')
			cout << " Choice 2\n";
		else
			cout << " Choice 3\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 4\n============================\nKicked\n\n";
	for (it = kicked.begin(); it != kicked.end(); it++)
		cout << it->getStudentName() << " " << it->getStudentGPA() << "\n";
	cout << "\n\n";

	final.push_back(chess);
	final.push_back(dancing);
	final.push_back(gaming);
	final.push_back(running);
	final.push_back(swimming);
	final.push_back(tenis);
	final.push_back(kicked);

	return final;
}




vector<vector<student>> round5(vector<vector<student>> data, sports spdata) {
	vector<student> chess, dancing, gaming, running, swimming, tenis, kicked;
	vector<student>::iterator it;
	vector<vector<student>> final;
	for (int i = 0; i < data.at(0).size(); i++) {
		chess.push_back(data.at(0).at(i));
	}
	for (int i = 0; i < data.at(1).size(); i++) {
		dancing.push_back(data.at(1).at(i));
	}
	for (int i = 0; i < data.at(2).size(); i++) {
		gaming.push_back(data.at(2).at(i));
	}
	for (int i = 0; i < data.at(3).size(); i++) {
		running.push_back(data.at(3).at(i));
	}
	for (int i = 0; i < data.at(4).size(); i++) {
		swimming.push_back(data.at(4).at(i));
	}
	for (int i = 0; i < data.at(5).size(); i++) {
		tenis.push_back(data.at(5).at(i));
	}
	for (int i = 0; i < data.at(6).size(); i++) {
		kicked.push_back(data.at(6).at(i));
	}
	bool b = 1;
	for (it = kicked.end(); it != kicked.begin(); it--) {
		srand(time(0));
		do {
			switch (random()) {
			case 1:
				if (chess.size() < spdata.chess) {
					chess.push_back(*it);
					kicked.pop_back();
					b = 0;
				}
				break;

			case 2:
				if (dancing.size() < spdata.dancing) {
					dancing.push_back(*it);
					kicked.pop_back();
					b = 0;
				}
				break;

			case 3:
				if (gaming.size() < spdata.gaming) {
					gaming.push_back(*it);
					kicked.pop_back();
					b = 0;
				}
				break;

			case 4:
				if (running.size() < spdata.running) {
					running.push_back(*it);
					kicked.pop_back();
					b = 0;
				}
				break;

			case 5:
				if (swimming.size() < spdata.swimming) {
					swimming.push_back(*it);
					kicked.pop_back();
					b = 0;
				}
				break;

			case 6:
				if (tenis.size() < spdata.tenis) {
					tenis.push_back(*it);
					kicked.pop_back();
					b = 0;
				}
				break;
			}
		} while (b != 0);
	}

	cout << "round 5\n============================\nChess\n\n";
	for (it = chess.begin(); it != chess.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'C')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'C')
			cout << " Choice 2\n";
		else if (it->getStudentChoice().at(2) == 'C')
			cout << " Choice 3\n";
		else
			cout << " Random\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 5\n============================\nDancing\n\n";
	for (it = dancing.begin(); it != dancing.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'D')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'D')
			cout << " Choice 2\n";
		else if (it->getStudentChoice().at(2) == 'D')
			cout << " Choice 3\n";
		else
			cout << " Random\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 5\n============================\nGaming\n\n";
	for (it = gaming.begin(); it != gaming.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'G')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'G')
			cout << " Choice 2\n";
		else if (it->getStudentChoice().at(2) == 'G')
			cout << " Choice 3\n";
		else
			cout << " Random\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 5\n============================\nRunning\n\n";
	for (it = running.begin(); it != running.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'R')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'R')
			cout << " Choice 2\n";
		else if (it->getStudentChoice().at(2) == 'R')
			cout << " Choice 3\n";
		else
			cout << " Random\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 5\n============================\nSwimming\n\n";
	for (it = swimming.begin(); it != swimming.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'S')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'S')
			cout << " Choice 2\n";
		else if (it->getStudentChoice().at(2) == 'S')
			cout << " Choice 3\n";
		else
			cout << " Random\n";
	}
	cout << "\n\n";
	clrscr();

	cout << "round 5\n============================\nTennis\n\n";
	for (it = tenis.begin(); it != tenis.end(); it++) {
		cout << it->getStudentName() << " " << it->getStudentGPA();
		if (it->getStudentChoice().at(0) == 'T')
			cout << " Choice 1\n";
		else if (it->stole == 1)
			cout << " Stolen from " << it->stolen << "\n";
		else if (it->getStudentChoice().at(1) == 'T')
			cout << " Choice 2\n";
		else if (it->getStudentChoice().at(2) == 'T')
			cout << " Choice 3\n";
		else
			cout << " Random\n";
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

int random() {
	for (int i = 0; i < 3; i++)
		return rand() % (1 - 6 + 1) + 1;
}