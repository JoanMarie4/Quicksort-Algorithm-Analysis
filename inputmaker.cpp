#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <bits/stdc++.h>
using namespace std;

bool compareRatio(int i1, int i2){
    return (i1 > i2);
}

int main(int argc, char *argv[]) { 
    int blah = argc; 
    blah++;
    int inputNum = stoi(argv[1]);
    vector<int> intList;
    string dir = "input/";

    ofstream outFS;
    string title = "inputRandom.txt";
    string output = dir + argv[1] + title;
    outFS.open(output);
    if(!outFS.is_open()){
            cout << "Problem opening file " << argv[1] << "inputRandom.txt" << "." << endl;
            return 1;
    }

    outFS << inputNum << endl;
    for(int i = 0; i < inputNum; i++){
        int r = (rand() % 1000);
        intList.push_back(r);
        outFS << r;
        if(i < inputNum-1){
            outFS << endl;
        }
    }

    outFS.close();
    title = "inputSorted.txt";
    output = dir + argv[1] + title;
    outFS.open(output);
    outFS << inputNum << endl;
    if(!outFS.is_open()){
            cout << "Problem opening file " << argv[1] << "inputSorted.txt" << "." << endl;
            return 1;
    }

    sort(intList.begin(), intList.end());
    for(int i = 0; i < inputNum; i++){
        outFS << intList[i];
        if(i < inputNum-1){
            outFS << endl;
        }
    }

    outFS.close();
    title = "inputReverseSorted.txt";
    output = dir + argv[1] + title;
    outFS.open(output);
        if(!outFS.is_open()){
            cout << "Problem opening file " << argv[1] << "inputReverseSorted.txt" << "." << endl;
            return 1;
    }

    outFS << inputNum << endl;
    sort(intList.begin(), intList.end(), compareRatio);
    for(int i = 0; i < inputNum; i++){
        outFS << intList[i];
        if(i < inputNum-1){
            outFS << endl;
        }
    }

    outFS.close();
    intList.clear();

}