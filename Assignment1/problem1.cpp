#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int addToArrayAsc(float sortedArray[], int numElements, float newValue);

int main(int argc, char * argv[]) {
    if (argc != 2) {
        cout << "error, incorrect input" << endl;
        return 0;
    }
    
    ifstream myFile(argv[1]); // opening file
    if (!myFile) {
        cout << "Failed to open the file." << endl;
        return 0;
    }
    float sortedArray[100];
    int numElements = 0;

    string inVal;
    while (getline(myFile,inVal)) {
        float newValue = stof(inVal); // read line and convert to float
        if (numElements == 0) {
            sortedArray[0] = newValue; // if blank, adds first value
            numElements = 1;
        }
        else if (numElements >= 100) {
            cout << "maximum array size (100) reached, ending program" << endl;
            break;
        }
        else {
            numElements = addToArrayAsc(sortedArray,numElements,newValue);
        }
        for (int i = 0; i < numElements; i++) {
            if (i == numElements -1 ) cout << sortedArray[i];
            else cout << sortedArray[i] << ",";
        }
        cout << endl;
    }
    myFile.close();
    return 1;
}

int addToArrayAsc(float sortedArray[], int numElements, float newValue) {
    float tempVal;
    sortedArray[numElements] = newValue; //newValue at end


    //bubble sorter
    for (int i = 0; i < numElements;i++) {
        for (int j = 0; j < numElements - i; j++) {
            if (sortedArray[j] > sortedArray[j+1]) {
                tempVal = sortedArray[j];
                sortedArray[j] = sortedArray[j+1];
                sortedArray[j+1] = tempVal;
            }
        }
    }
    numElements += 1;

    return numElements;
}