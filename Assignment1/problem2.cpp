#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

struct studentData {
    string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam;
    double average;
};

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, 
int exam, int length);

char calcLetter(double avg);

int calcGradeBnds(char lower, char upper, int bounds[]);

void printList(const studentData students[], int length);

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, 
int exam, int length) {
    studentData studentStruct;
    studentStruct.studentName = studentName;
    studentStruct.homework = homework;
    studentStruct.recitation = recitation;
    studentStruct.quiz = quiz;
    studentStruct.exam = exam;
    studentStruct.average = (float)(homework + recitation + quiz + exam)/4;
    students[length] = studentStruct;
}

char calcLetter(double avg) {
    char letter;
    if (avg >= 90) letter = 'A';
    else if (80 <= avg) letter = 'B';
    else if (70 <= avg) letter = 'C';
    else if (60 <= avg) letter = 'D';
    else letter = 'F';

    return letter;
}

int calcGradeBnds(char lower, char upper, int bounds[]) {
    if (lower == 'A') bounds[0] = 90;
    else if (lower == 'B') bounds[0] = 80;
    else if (lower == 'C') bounds[0] = 70;
    else if (lower == 'D') bounds[0] = 60;
    else if (lower == 'F') bounds[0] = 0;
    else return 1;

    if (upper == 'A') bounds[1] = 100;
    else if (upper == 'B') bounds[1] = 89.9;
    else if (upper == 'C') bounds[1] = 79.9;
    else if (upper == 'D') bounds[1] = 69.9;
    else if (upper == 'F') bounds[1] = 59.9;
    else return 1;

    return 0;
}

void printList(const studentData students[], int length) {
    for (int i = 0; i < length; i++) {
        cout << students[i].studentName << " earned " << students[i].average << " which is a(n) " 
        << calcLetter(students[i].average) << endl;
    }
}

int main(int argc, char * argv[]) {
     if (argc != 5) {
         cout << "error, invalid number of inputs" << endl << "format:" << endl << "<program> <input file> <output file> <lower bound> <upper bound>" << endl;
         return 0;
     }

    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    if (!inFile) {
        cout << "input file not opened, check your arguments" << endl;
        return 0;
    }
    if (!outFile) {
        cout << "output file not opened, check your arguments" << endl;
        return 0;
    }

    studentData students[10];
    int length = 0;
    string inVal;
    string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam;
    while(getline(inFile,inVal)) {
        stringstream tmp(inVal);

        getline(tmp,studentName,',');
        getline(tmp,inVal,',');
        homework = stoi(inVal);
        getline(tmp,inVal,',');
        recitation = stoi(inVal);
        getline(tmp,inVal,',');
        quiz = stoi(inVal);
        getline(tmp,inVal,',');
        exam =  stoi(inVal);
        
        addStudentData(students, studentName, homework, recitation, quiz, exam, length);
        length++;
    } 
    inFile.close();
    printList(students, length);

    bool check;
    int bounds[2];
    check = calcGradeBnds(*argv[3], *argv[4], bounds);
    if (check) {
        cout << "error, invalid grade bounds, check args" << endl;
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if ((students[i].average >= bounds[0]) && (students[i].average <= bounds[1])) {
            char letterGrade = calcLetter(students[i].average);
            outFile << students[i].studentName << ',' << students[i].average << ',' << letterGrade << endl;
        }
    }
    outFile.close();
    return 1;
}
