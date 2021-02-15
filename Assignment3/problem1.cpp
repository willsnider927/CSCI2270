#include<iostream>
#include<fstream>
#include<string>

using namespace std;


bool append(string* &str_arr, string s, int &numEntries, int &arraySize);

bool append(string* &str_arr, string s, int &numEntries, int &arraySize) {
    if (numEntries >= arraySize) { //if needing double
        string* temp = new string[arraySize*2];
        for (int i = 0; i < arraySize; i++) {
            temp[i] = str_arr[i];
        }
        delete[] str_arr;
        str_arr = temp;
        arraySize = arraySize*2;
        str_arr[numEntries] = s;
        numEntries += 1;
        return 1;
    }
    else { //if not needing double
        str_arr[numEntries] = s;
        numEntries += 1;
        return 0;
    }
}