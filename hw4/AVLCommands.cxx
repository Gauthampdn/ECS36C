#include "AVL.h"
#include<iostream>
#include<fstream>
#include"json.hpp"

// copied from BST

int main(int argc, char const *argv[])
{

    if (argc != 2) {
        // error if not proper number of aruguments
        std::cerr << "Not proper number of arguments. There should be 2 arguments: executable json_file_name" << std::endl;  
        return 0;
    }


    std::ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;

    if(file.is_open()){
        file >> jsonObject;
    }

    file.close();

    AVL tree;

    for(auto itr = jsonObject.begin(); itr != std::prev(jsonObject.end()); itr++){
        if(itr.value()["operation"] == "Insert"){
           size_t key = itr.value()["key"];
           tree.Insert(key);  

    std::string balancedAVLTree = tree.JSON();
        }
    }

    std::string balancedAVLTree = tree.JSON();
    std::cout << balancedAVLTree << std::endl;
    
    return 0;
}