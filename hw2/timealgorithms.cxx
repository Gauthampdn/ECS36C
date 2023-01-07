#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<chrono>
#include"json.hpp"
#include"insertionsort.h"
#include"mergesort.h"
#include"quicksort.h"

using namespace std;



int main(int argc, char** argv) {


    std::ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
    }
    file.close();

    nlohmann::json jsonTime;

    int InsertionSortCompares = 0;
    int InsertionSortMemaccess = 0;
    int MergeSortCompares = 0;
    int MergeSortMemaccess = 0;
    int QuickSortCompares = 0;
    int QuickSortMemaccess = 0;



    std::cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess" << std::endl;

    std::chrono::high_resolution_clock::time_point start;  // defning the clock

    vector<int> numList;

    int arraySize = jsonObject["metadata"]["arraySize"];

        for(auto itr = jsonObject.begin(); itr != prev(jsonObject.end()); ++itr) {
            for(int i = 0;  i < arraySize; i++){
                numList.push_back(itr.value()[i]);
            }



            vector<int> Mergelist = numList;
            vector<int> Insertionlist = numList;
            vector<int> Quicklist = numList;
            


            std::cout << itr.key() << ',';



            start = std::chrono::high_resolution_clock::now(); //starting the clock
            InsertionSort(&Insertionlist, InsertionSortCompares, InsertionSortMemaccess);
            auto end = std::chrono::high_resolution_clock::now();  // ending the clock
            double elapsed_us = std::chrono::duration<double, std::micro>(end-start).count(); // difference in the starting and end timings

            std::cout << elapsed_us << ',';
            std::cout << InsertionSortCompares << ',';
            std::cout << InsertionSortMemaccess << ',';


            start = std::chrono::high_resolution_clock::now(); //starting the clock
            MergeSort(&Mergelist, MergeSortCompares, MergeSortMemaccess); 
            end = std::chrono::high_resolution_clock::now();  // ending the clock
            elapsed_us = std::chrono::duration<double, std::micro>(end-start).count(); // difference in the starting and end timings

            std::cout << elapsed_us << ',';
            std::cout << MergeSortCompares << ',';
            std::cout << MergeSortMemaccess << ',';


            start = std::chrono::high_resolution_clock::now(); //starting the clock
            QuickSort(&Quicklist, QuickSortCompares, QuickSortMemaccess);
            end = std::chrono::high_resolution_clock::now();  // ending the clock
            elapsed_us = std::chrono::duration<double, std::micro>(end-start).count(); // difference in the starting and end timings

            std::cout << elapsed_us << ',';
            std::cout << QuickSortCompares << ',';
            std::cout << QuickSortMemaccess << std::endl;



            jsonTime[itr.key()] = Mergelist;
            numList.clear();

            MergeSortMemaccess = 0;
            MergeSortCompares = 0;
            InsertionSortCompares = 0;
            InsertionSortMemaccess = 0;
            QuickSortCompares = 0;
            QuickSortMemaccess = 0;

        }
        // std::cout << jsonTime.dump(2) << "\n";






}