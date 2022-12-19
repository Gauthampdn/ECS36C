# 36C-2
## Objectives of the assignment 
In this program you will study and experiment with InsertionSort, MergeSort,
and QuickSort. There are multiple objectives of this assignment:
1. introduce the JSON (JavaScript Object Notation) and CSV (comma sep-
arated values) data formats, which are frequently used in professional
settings,
2. examine the wallclock running time of InsertionSort, MergeSort, and Quick-
Sort,
1
3. understand fine-grained details of algorithm analysis (wallclock vs. worst-
case Big-O vs. average-case Big-O),
4. introduce automated testing, and
5. use your automated tests to detect code with bugs.

### Executable #1
Executable Name: sortedverification
Source: sortedverification.cxx
Usage: sortedverification file.json
This program takes the name of a JSON file as a command-line argument
file.json that represents the output of a sorting algorithm and verifies that
each sample is a sorted array. If a sample array is not sorted, there must be
some position i such that the ith element is equal to or larger than the i + 1st
element. We call this a consecutive inversion. For example, if A = [−2, 0, 3, 2, 5]
there is a consecutive inversion at location i = 2 because A[2] = 3 > 2 = A[3].
For example, the samples

Sample1 = [−1641818748, 1952682320, −195384256, −1702150187], and
Sample2 = [−683761375, −406924096, −362070867, −592214369]

are defined by the following input file SampleExample.json:

```
{
"Sample1": [-319106570,811700988,1350081101,1602979228],
"Sample2": [-319106570,811700988,797039,-1680733532],
"metadata": {
"arraySize":4,
"numSamples":2
}
}
```

Sample2 has consecutive inversions at index 1 and 2, and running
```./sortedverification SampleExample.json```
prints the contents of a JSON object to the screen (i.e. to stdout):
```
{
  "Sample2": {
    "ConsecutiveInversions": {
      "1": [811700988, 797039],
      "2": [797039, -1680733532]
    },

    "sample": [-319106570, 811700988, 797039, -1680733532]
  },
  "metadata": {
    "arraySize": 4,
    "file": "SampleExample.json",
    "numSamples": 2,
    "samplesWithInversions": 1
  }
}
```
Sample1 has no inversions so its data is not printed to the JSON output above.
Notice that if the consecutive inversions of a sample are added to the JSON
object, the sample data (the array) is also added to the JSON object.

### Executable #2
Executable Name: consistentresultverification
Source: consistentresultverification.cxx
```Usage: consistentresultverification file1.json file2.json.```

This program takes two command-line arguments file1.json and file2.json
that contain JSON objects representing the output of two sorting algorithms,
and verifies that these files represent the same samples or reports their differences.


These differences are output when I run
```./consistentresultverification.sh SampleExample.json AlmostSampleExample.json```

The program outputs the following:
```{
  "Sample1": {
    "AlmostSampleExample.json": [-319106570, 8117009, 13500811, 1602979228],
    "Mismatches": {
      "1": [811700988, 8117009],
      "2": [1350081101, 13500811]
    },
    "SampleExample.json": [-319106570, 811700988, 1350081101, 1602979228]
  },
  "metadata": {
    "File1": {
      "arraySize": 4,
      "name": "SampleExample.json",
      "numSamples": 2
    },
    "File2": {
      "arraySize": 4,
      "name": "AlmostSampleExample.json",
      "numSamples": 2
    },
    "samplesWithConflictingResults": 1
  }
}
```

The metadata field now contains information about the files being read in. The
key Sample1 has information because it differs between SampleExample.json
and AlmostSampleExample.json. Its value contains the sample from each file
along with the differences between the asmples. Differences are listed in the
Mismatches key, which contains a list of positions that mismatch and their
contents. Note that the key-value pair "1": [ 811700988, 8117009 ] exists
because the second entry of Sample1 in SampleExample.json is 811700988 and
AlmostSampleExample.json is 8117009.

### Executable #3
Executable Name: timealgorithms Source: timealgorithms.cxx
Usage: timealgorithms file.json
This program takes the name of a JSON file as a command-line argument
5
(file.json) that represents a collection of arrays to be sorted (an input file
for the sorting algorithms) and runs InsertionSort, MergeSort, and QuickSort
on all samples in the file, measures various statistics, and prints these statistics
to a CSV file.

InsertionSortTime: The wallclock time of running InsertionSort on this row’s sample
InsertionSortCompares: The number of compares used when running InsertionSort on this row’s sample
InsertionSortMemaccess: The number of memory accesses when running InsertionSort on this row’s sample
MergeSortTime: The wallclock time of running MergeSort on this row’s sample
MergeSortCompares: The number of compares used when running MergeSort on this row’s sample
MergeSortMemaccess: The number of memory accesses when running MergeSort on this row’s sample
QuickSortTime: The wallclock time of running QuickSort on this row’s sample
QuickSortCompares: The number of compares used when running QuickSort on this row’s sample
QuickSortMemaccess: The number of memory accesses when running QuickSort on this row’s sample
