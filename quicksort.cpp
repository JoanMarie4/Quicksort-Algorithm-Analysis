#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <cmath>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

long lomutoSwaps = 0;
long hoaresSwaps = 0;
long randomHoareSwaps = 0;
long randomLomutoSwaps = 0;

int lomutoPartition(vector<int> &intList, int p, int r){
    int x = intList[r];
    int i = p - 1;
    for(int j = p; j <= r-1; j++){
        if(intList[j] <= x){
            i = i + 1;
            swap(intList[i],intList[j]);
            lomutoSwaps++;
        }
    }
    int temp = intList[r];
    intList[r] = intList[i+1];
    intList[i+1] = temp;
    return i+1;
}

int randomPartitionLomuto(vector<int> &intList, int p, int r){
    int pivot = p + (rand() % (r - p + 1));
    int temp = intList[r];
    intList[r] = intList[pivot];
    intList[pivot] = temp;
    int x = intList[r];
    int i = p - 1;
    for(int j = p; j <= r-1; j++){
        if(intList[j] <= x){
            i = i + 1;
            swap(intList[i],intList[j]);
            randomLomutoSwaps++;
        }
    }
    int temp1 = intList[r];
    intList[r] = intList[i+1];
    intList[i+1] = temp1;
    return i+1;
    
}

int hoaresPartition(vector<int> &intList, int p, int r){
    int x = intList[p];
    int i = p - 1;
    int j = r + 1;
    while(true){
        do{
            j--;
        }
        while(intList[j] > x);
        do{
            i++;
        }
        while(intList[i] < x);
        if(i < j){
            swap(intList[i],intList[j]);
            hoaresSwaps++;
        }else{
            return j;
        }

    }
}

int randomPartitionHoare(vector<int> &intList, int p, int r){
    int pivot = r - (rand() % (r - p + 1));
    int temp = intList[p];
    intList[p] = intList[pivot];
    intList[pivot] = temp;
    int x = intList[p];
    int i = p - 1;
    int j = r + 1;
    while(true){
        do{
            j--;
        }
        while(intList[j] > x);
        do{
            i++;
        }
        while(intList[i] < x);
        if(i < j){
            swap(intList[i],intList[j]);
            randomHoareSwaps++;
        }else{
            return j;
        }

    }
}

bool sortCheck(vector<int> intList){
    for(unsigned int i = 0; i < intList.size() - 1; i++){
        if(intList[i] > intList[i+1]){
            cout << i << " " << intList[i] << endl;
            return false;
        }
    }
    return true;
}

void quicksort(vector<int> &intList, int p, int r, int partNum){
    if(p < r){
        if(partNum == 0){
            int q = lomutoPartition(intList, p, r);
            quicksort(intList, p, q-1, 0);
            quicksort(intList, q+1, r, 0);
        } else if(partNum == 1){
            int q = hoaresPartition(intList, p, r);
            quicksort(intList, p, q, 1);
            quicksort(intList, q+1, r, 1);
        } else if(partNum == 2){
            int q = randomPartitionLomuto(intList, p, r);
            quicksort(intList, p, q-1, 2);
            quicksort(intList, q+1, r, 2);
        } else if(partNum == 3){
            int q = randomPartitionHoare(intList, p, r);
            quicksort(intList, p, q, 3);
            quicksort(intList, q+1, r, 3);
        }
    }
}

int main(int argc, char *argv[]) {  
    //if argc isnt 4, program cant run
    if(argc != 3){
        cout << "3 Arguments required, halting program." << endl;
        return 1;
    }
    //initializations and declarations
    string outdir = "output/";
    string indir = "input/";
    string inputFile = indir + argv[1];
    string outputFile = outdir + argv[2];
    int intNum = -1;

    //opening output file
    ofstream outFS;
    outFS.open(outputFile);
    if(!outFS.is_open()){
            cout << "Problem opening file " << outputFile << "." << endl;
            return 1;
    }
    
    //initialize intList, open input
    vector<int> intListLomuto;
    vector<int> intListHoares;
    vector<int> intListRandomLomuto;
    vector<int> intListRandomHoares;
    ifstream inFS;
    inFS.open(inputFile);
    if(!inFS.is_open()){
        cout << "Problem opening file " << inputFile << "." << endl;
        return 1;
    }

    //reading in number of integers to be considered
    string inLine;
    while(getline(inFS, inLine)){
        if(isdigit(inLine.at(0))){
            intNum = stoi(inLine.substr(0, inLine.find_first_of(' ')));
        } else{
            cout << "Input File formatted improperly. Halting program." << endl;
            return 1;
        }

        for(int i = 0; i < intNum; i++){
            getline(inFS, inLine);
            intListLomuto.push_back(stoi(inLine));
            intListHoares.push_back(stoi(inLine));
            intListRandomLomuto.push_back(stoi(inLine));
            intListRandomHoares.push_back(stoi(inLine));
            inLine = "";
        }
        
        intNum--;
        //Running lomutos partition
        auto start = high_resolution_clock::now();
        quicksort(intListLomuto, 0, intNum, 0);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double time = duration.count() * pow(10, -6);

        outFS << "Lomuto's Partitioning Time: " << fixed << time << " nanoseconds" <<  endl;
        outFS << "Lomuto's Partitioning Swap Count: " << lomutoSwaps << endl;
        outFS << "Lomuto's sorted: " << sortCheck(intListLomuto) << endl;

        //Running Hoares partition
        start = high_resolution_clock::now();
        quicksort(intListHoares, 0, intNum, 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        time = duration.count() * pow(10, -6);

        outFS << "Hoare's Partitioning Time: " << fixed << time << " nanoseconds" <<  endl;
        outFS << "Hoare's Partitioning Swap Count: " << hoaresSwaps << endl;
        outFS << "Hoares's sorted: " << sortCheck(intListHoares) << endl;
        
        //Running Lomuto's w/ random partition
        start = high_resolution_clock::now();
        quicksort(intListRandomLomuto, 0, intNum, 2);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        time = duration.count() * pow(10, -6);

        outFS << "Lomuto's Random Partitioning Time: " << fixed << time << " nanoseconds" << endl;
        outFS << "Lomuto's Random Partitioning Swap Count: " << randomLomutoSwaps << endl;
        outFS << "Lomuto's Random sorted: " << sortCheck(intListRandomLomuto) << endl;

        //Running Hoare's w/ random partition
        start = high_resolution_clock::now();
        quicksort(intListRandomHoares, 0, intNum, 3);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        time = duration.count() * pow(10, -6);

        outFS << "Hoare's Random Partitioning Time: " << fixed << time << " nanoseconds" << endl;
        outFS << "Hoare's Random Partitioning Swap Count: " << randomHoareSwaps << endl;
        outFS << "Hoare's Random sorted: " << sortCheck(intListRandomHoares);

        outFS.close();

        /**outFS.open("LomutoOutput.txt");
        for(unsigned int i = 0; i < intListLomuto.size(); i++){
            outFS << intListLomuto[i] << endl;
        }
        outFS.close();**/
        intListLomuto.clear();

        /**outFS.open("HoaresOutput.txt");
        for(unsigned int i = 0; i < intListHoares.size(); i++){
            outFS << intListHoares[i] << endl;
        }
        outFS.close();**/
        intListHoares.clear();

        /**outFS.open("LomutoRandomOutput.txt");
        for(unsigned int i = 0; i < intListRandomLomuto.size(); i++){
            outFS << intListRandomLomuto[i] << endl;
        }
        outFS.close();**/
        intListRandomLomuto.clear();

        /**outFS.open("HoaresRandomOutput.txt");
        for(unsigned int i = 0; i < intListRandomHoares.size(); i++){
            outFS << intListRandomHoares[i] << endl;
        }
        outFS.close();**/
        intListRandomHoares.clear();
    }


}