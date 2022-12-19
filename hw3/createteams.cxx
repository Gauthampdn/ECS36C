#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <cstdlib>
#include "json.hpp"
#include "teamdata.h"
#include "priorityqueue.h"

using namespace std;
using nlohmann::json;

int main(int argc, char** argv) {

    if (argc != 2) {
        // error if not proper number of aruguments
        std::cerr << "Not proper number of arguments. There should be 2 arguments" << std::endl;  
        return 0;
    }

    std::ifstream file1;  //opening file and reading into json object

    nlohmann::json teamWins;  
    file1.open(argv[1]);   
    if (file1.is_open()){
        file1 >> teamWins;
    }
    file1.close();

    int numplayers = teamWins["metadata"]["numPlayers"];  // getting meta data values
    int numteams = (numplayers/2);
    int max = (numplayers*(numplayers-1))/2;  // max is sum of 1 thru number of players due to match ups
    
    
    PriorityQueue teamnodes(max);

    for(auto itr = teamWins["teamStats"].begin(); itr != teamWins["teamStats"].end(); itr++){ //iterate thru the team match ups

        int player1 = itr.value()["playerOne"];
        int player2 = itr.value()["playerTwo"];
        double winPercent = itr.value()["winPercentage"];
        double winDiff = abs(50-winPercent);  // find the asolute value difference from 50 since that is a fair team
        KeyValuePair match = std::make_pair(winDiff, std::make_pair(player1, player2)); // push the win difference and the player data to a Key value Pair
        teamnodes.insert(match);        // push the pair into the queue
    }

   nlohmann::json resultJson = teamnodes.JSON();

   std::vector<std::pair<int, int>> Pairs;
    
        int p1 = teamnodes.min().second.first;
        int p2 = teamnodes.min().second.second;

        std::pair<int, int> matchup;
        matchup.first = p1;
        matchup.second= p2;
        Pairs.push_back(matchup);  // the first min in the queue will always be in since it will be the closest to 50
        teamnodes.removeMin(); // removing the node
    
        int currentpairs = 1;   // inrementing the number of pairs

    while(currentpairs < numteams){   // keep iterating thru until there are all pairs for players
        p1 = teamnodes.min().second.first;
        p2 = teamnodes.min().second.second;
        int j = 0;   // instantiating j
        for( j = 0; j < currentpairs;){
            if(Pairs[j].first == p1 || Pairs[j].second == p1 || Pairs[j].first == p2 || Pairs[j].second == p2){           
                teamnodes.removeMin(); // if the current pair in the heap has values in the list of match ups, remove that pair
                p1 = teamnodes.min().second.first;
                p2 = teamnodes.min().second.second;
                j=0;
                // set the new pair values to the nect minimum and then set the j(the checker) all the way back to the front of the matchups
            }
            else{
                j++;
                }            
        
        }
                // if there is no match ups for the current pair, push that pair into the matchup list
                std::pair<int, int> matchup;
                matchup.first = p1;
                matchup.second= p2;
                Pairs.push_back(matchup);
                currentpairs++;
                teamnodes.removeMin();        
        }
    
    json allPairs;
    allPairs["teams"] = Pairs;
    std::cout << allPairs.dump(2) << std::endl;
}
