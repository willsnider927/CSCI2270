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

void printList(const studentData students[], int length);

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, 
int exam, int length) {
    studentData studentStruct;
    studentStruct.studentName = studentName;
    studentStruct.homework = homework;
    studentStruct.recitation = recitation;
    studentStruct.quiz = quiz;
    studentStruct.exam = exam;
    studentStruct.average = (homework + recitation + quiz + exam)/4;
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

void printList(const studentData students[], int length) {
    for (int i = 0; i < length; i++) {
        cout << students[i].studentName << " earned " << students[i].average << " which is a(n) " 
        << calcLetter(students[i].average) << endl;
    }
}

int main(int argc, char * argv[]) {
    // if (argc != 5) {
    //     cout << "error, invalid number of inputs" << endl << "format:" << endl << "<program> <input file> <output file> <lower bound> <upper bound>" << endl;
    //     return 1;
    // }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cout << "file not opened, check your arguments" << endl;
        return 1;
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
}
