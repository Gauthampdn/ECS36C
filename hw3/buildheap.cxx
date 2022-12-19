#include <iostream>
#include <fstream>
#include "priorityqueue.h"
#include "json.hpp"

int main(int argc, char** argv) {

    if (argc != 2) {
        // error if not proper number of aruguments
        std::cerr << "Not proper number of arguments. There should be 2 arguments" << std::endl;  
        return 0;
    }

    std::ifstream file;   // open the json file and copy it into a json object
    file.open(argv[1]);
    nlohmann::json jsonObject;
    
    if(file.is_open()){
        file >> jsonObject;
    }

    file.close();
    
    int maxHeapSize = jsonObject["metadata"]["maxHeapSize"];           // get the max heap size
    int numOperations = jsonObject["metadata"]["numOperations"];        // get the total number of operations
    
    
    PriorityQueue heap(maxHeapSize);


    for (auto itr = jsonObject.begin(); itr != prev(jsonObject.end()); itr++){  // iterate thru the json object
        if(itr.value()["operation"] == "insert"){
            double Key = itr.value()["key"];
            heap.insert(Key);                           // insert if the operation from the json says insert
        }
        if(itr.value()["operation"] == "removeMin"){
            heap.removeMin();                           // removeMin if the operation from the json says removeMin
        }
    };

    nlohmann::json resultJson = heap.JSON();            // turn the data from the heap priority queue into a json object
    resultJson["metadata"]["maxHeapSize"] = maxHeapSize;        // copying metadata
    resultJson["metadata"]["numOperations"] = numOperations;
    std::cout << resultJson.dump(2)<< std::endl;

}
