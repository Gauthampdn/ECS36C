#include<iostream>
#include<fstream>
#include"BST.h"
#include"json.hpp"
int main(int argc, char const *argv[])
{
    std::ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    if(file.is_open()){
        file >> jsonObject;
    }
    file.close();

    BST tree;

    for (auto itr = jsonObject.begin(); itr != std::prev(jsonObject.end()); itr++){
        if(itr.value()["operation"] == "Insert"){
           size_t key = itr.value()["key"];
           tree.Insert(key);
        }
    }
    std::string balancedAVLTree = tree.JSON();
    std::cout << balancedAVLTree << std::endl;
    
    return 0;
}