#include<iostream>
#include<string>
#include <sstream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include"json.hpp"

int main(int argc, char** argv) {

    std::ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
    }

    file.close();

    nlohmann::json flipsJSON;
    flipsJSON["metadata"] = jsonObject["metadata"];

    int arraySize = jsonObject["metadata"]["arraySize"];
    
    bool foundConsec;
    int numConsec = 0;
/*
    for (auto itr = jsonObject.begin(); itr != prev(jsonObject.end()); ++itr) {
        std::cout << "key: " << itr.key() << " value: " << itr.value() << '\n';
    }
*/
    for (auto itr = jsonObject.begin(); itr != prev(jsonObject.end()); ++itr) {  

        foundConsec = false;
        for(int i = 0; i < arraySize-1; i++){
            if(itr.value()[i] > itr.value()[i+1]){

                flipsJSON[itr.key()]["ConsecutiveInversions"];
                flipsJSON[itr.key()]["sample"] = jsonObject[itr.key()];

                auto x = itr.value()[i];
                auto y = itr.value()[i+1];

                int pair[2]= { itr.value()[i], itr.value()[i+1] };
                flipsJSON[itr.key()]["ConsecutiveInversions"][std::to_string(i)] = pair;

                foundConsec = true;
            }
        }

        if(foundConsec){
            numConsec++;
        }
    
    }
    
    flipsJSON["metadata"]["file"] = argv[1];
    flipsJSON["metadata"]["samplesWithInversions"] = numConsec;


    std::cout << flipsJSON.dump(2) << "\n";

}