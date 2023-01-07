// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void QuickSort(std::vector<int>* numbers, int& numComp, int& numMem);
void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int& numComp, int& numMem);
int Partition(std::vector<int>* numbers, int i, int k, int& numComp, int& numMem);