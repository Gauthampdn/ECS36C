// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void MergeSort(std::vector<int>* numbers, int& numComp, int& numMem);
void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int& numComp, int& numMem);
void Merge(std::vector<int>* numbers, int i, int j, int k, int& numComp, int& numMem);