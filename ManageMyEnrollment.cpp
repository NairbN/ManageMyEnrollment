//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_NUM_OF_CLASSES = 100;
const double FEE_PER_UNIT = 31.0;

class Course {
private:
	string name;
	int units;
public:
	Course(string name1, int units1) {
		name = name1;
		units = units1;
	}
	Course() {

	}

	string getName() {
		return name;
	}

	void setName(string name) {
		name = this->name;
	}

	int getUnits() {
		return units;
	}

	void setUnits(int units) {
		units = this->units;
	}

	bool search(string word) {
		size_t found = name.find(word);
		if (found == string::npos) {
			return false;
		}
		else {
			return true;
		}
	}

	bool greaterOrEqualUnits(int num) {
		if (units >= num) {
			return true;
		}
		else {
			return false;
		}
	}

	string toString() {
		string str = "Class: " + name + "\t\t" + "Units: " + to_string(units);
		return str;
	}
};

void enroll(Course* classList, int& numOfClasses, string name, int units) {
	Course newCourse = Course(name, units);
	classList[numOfClasses] = newCourse;
	numOfClasses++;
}

int detail(Course classList[], int numOfClasses, string* printLines) {
	int numLines = 0;
	int totalUnits = 0;
	for (int i = 0; i < numOfClasses; i++) {
		printLines[i] = classList[i].toString();
		totalUnits += classList[i].getUnits();
		numLines++;
	}
	printLines[numOfClasses] = "Total classes: " + to_string(numOfClasses);
	printLines[numOfClasses + 1] = "Total units: " + to_string(totalUnits);
	string num_text = to_string(totalUnits * FEE_PER_UNIT + 0.0);
	printLines[numOfClasses + 2] = "Total fee: $" + num_text.substr(0, num_text.find(".") + 3);
	numLines += 3;
	return numLines;
}

int search(Course classList[], int numOfClasses, string* printLines , string word) {
	int numLines = 0;
	for (int i = 0; i < numOfClasses; i++) {
		if (classList[i].search(word)) {
			printLines[i] = classList[i].toString();
			numLines++;
		}
	}
	return numLines;
}

int searchUnits(Course classList[], int numOfClasses, string* printLines, int num) {
	int numLines = 0;
	for (int i = 0; i < numOfClasses; i++) {
		if (classList[i].greaterOrEqualUnits(num)) {
			printLines[i] = classList[i].toString();
			numLines++;
		}
	}
	return numLines;
}

bool readData(Course* classList, int& numOfClasses, string fileName) {
	ifstream data(fileName);
	if (data.is_open()) {
		string nameClass;
		int units;
		while (data >> units) {
			data.ignore();
			getline(data, nameClass);
			enroll(classList, numOfClasses, nameClass, units);
		}
		return true;
	}
	else {
		return false;
	}
}



int main(int argc, char* argv[]) {
	string command;
	int numOfClasses = 0;
	Course classList[MAX_NUM_OF_CLASSES];
	if (argc >= 2) {
		if (!readData(classList, numOfClasses, argv[1])) {
			cout << "Enrollment file is not found." << endl;
		}
	}
	do {
		cout << "Please enter a command: ";
		cin >> command;
		if (command == "enroll") {
			string name;
			int units;
			cin.ignore();
			cout << "Please enter the class name: ";
			getline(cin, name);
			cout << "Please enter the number of units for this class: ";
			cin >> units;
			enroll(classList, numOfClasses, name, units);
			cout << "You are enrolled. " << endl;
		}
		else if (command == "detail") {
			cout << "List of classes: " << endl;
			string printLines[MAX_NUM_OF_CLASSES + 3];
			int numLines = detail(classList, numOfClasses, printLines);
			for(int i = 0; i < numLines; i++){
				cout << printLines[i] << endl;
			}
		}
		else if (command == "search") {
			string word;
			cout << "Please enter search word: ";
			cin >> word;
			string printLines[MAX_NUM_OF_CLASSES];
			int numLines = search(classList, numOfClasses, printLines, word);
			if (numLines == 0) {
				cout << "Search did not match any class." << endl;
			}
			else {
				for (int i = 0; i < numLines; i++) {
					cout << printLines[i] << endl;
				}
			}
		}
		else if (command == "units>=") {
			int num;
			cout << "Please enter search units: ";
			cin >> num;
			string printLines[MAX_NUM_OF_CLASSES];
			int numLines = searchUnits(classList, numOfClasses, printLines, num);
			if (numLines == 0) {
				cout << "Search did not match any class." << endl;
			}
			else {
				for (int i = 0; i < numLines; i++) {
					cout << printLines[i] << endl;
				}
			}
		}
		else if (command == "help") {
			cout << "List of available commands:" << endl
				<< "enroll  - to enroll in a class" << endl
				<< "detail  - to list the enrollment in details" << endl
				<< "search  - to search for a word in the class list" << endl
				<< "units>= - to search for classes with units greater and equal" << endl
				<< "help    - to display list of valid commands" << endl
				<< "exit    - to exit the program" << endl;
		}
		else if (command == "exit") {
			cout << "Thank you." << endl;
			break;
		}
		else {
			cout << "Invalid command. Please enter \"help\" for the list of valid commands." << endl;
		}
		cout << "======================================" << endl;
	} while (command != "exit");
	return 0;
}