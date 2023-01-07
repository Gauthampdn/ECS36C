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
    nlohmann::json json1;
    if (file.is_open()) {
        file >> json1;
    }
    file.close();

    file.open(argv[2]);
    nlohmann::json json2;
    if (file.is_open()) {
        file >> json2;
    }
    file.close();

    nlohmann::json jsonResult;


    int arraySize = json1["metadata"]["arraySize"];
    
    bool foundConsec;
    int numConsec = 0;




    for (auto itr1 = json1.begin(); itr1 != prev(json1.end()); ++itr1) {
        for (auto itr2 = json2.begin(); itr2 != prev(json2.end()); ++itr2) {  

            foundConsec = false;
            if( itr1.key() == itr2.key()){
                for(int i = 0; i < arraySize; i++){


                    jsonResult[itr1.key()];
                    jsonResult[itr1.key()][argv[1]] = json1[itr1.key()];
                    jsonResult[itr1.key()][argv[2]] = json2[itr2.key()];
                    jsonResult[itr1.key()]["Mismatches"];

               //     std::cout << itr1.key() << std::endl;
                //   std::cout << itr2.key() << std::endl;

                    if(itr1.value()[i] != itr2.value()[i]){
               //         std::cout << itr1.value()[i] << std::endl;
                //       std::cout << itr2.value()[i] << std::endl;
                    foundConsec = true;
                    int pair[2]= {itr1.value()[i] , itr2.value()[i]};
                     jsonResult[itr1.key()]["Mismatches"][std::to_string(i)] = pair;

                    }
                }
            }


        if(foundConsec){
            numConsec++;
        }

/*
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
    
*/

    }
    }
    

    


    jsonResult["metadata"]["File1"] = json1["metadata"];
    jsonResult["metadata"]["File1"]["name"] = argv[1];
    jsonResult["metadata"]["File2"] = json2["metadata"];
    jsonResult["metadata"]["File2"]["name"] = argv[2];
    jsonResult["metadata"]["samplesWithConflictingResults"] = numConsec;


    std::cout << jsonResult.dump(2) << "\n";

}