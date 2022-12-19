//Gautham Pandian
//ECS36C P.Frid

#include<iostream>
#include<string>
#include <sstream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<chrono>

class book {

    // book class with ISBN, language and condition as well as setters and getters for all
    public:
        int ISBN;
        std::string language;
        std::string condition;
    void setISBN(int ISBNNum) {
        ISBN =ISBNNum;
    }
    void setcondition(std::string conditionVal) {
        condition = conditionVal;
    }
    void setlanguage(std::string languageVal) {
        language = languageVal;
    }
    int getISBN() {
        return ISBN;
    }
    std::string getcondition() {
        return condition;
    }
    std::string getlanguage() {
        return language;
    }

};


//overloading
std::ostream &operator<<(std::ostream &output, std::vector<book> v);
bool operator==(const book& lhs, const book& rhs);
bool operator>(const book& lhs, const book& rhs);
// we dont need a operator< since we can use the == and > operator together for it

bool fileRead(std::string str, std::vector<book> &v);
bool compare(book x, book y);
bool binarysearch(std::vector<book> list, std::vector<book> reqs, int current);
bool linearsearch(std::vector<book> list, std::vector<book> reqs, int current);
void result(std::string filename, int foundBooks);


bool fileRead(std::string str, std::vector<book> &v) {
    std::ifstream stream;
    stream.open(str); // opening the file
    
    int ISBN; // data of isbn to be stored after converting it into an integer
    std::string stringData;   // incoming data from file stored in a string, for both condition and language
    
    if (stream.fail()) {
        std::cout << "Error in opening: "<< str << std::endl;  // error is the file to be read does not exist
        return false;
    }

    book bp;   // create an object of the book class

    while (!stream.eof()) {
        getline(stream, stringData, ',');      //retreiving the values from each line of the data value
        ISBN = atoi(stringData.c_str());
        bp.setISBN(ISBN);              //setting the values into the object
        getline(stream, stringData, ',');
        bp.setlanguage(stringData);
        getline(stream, stringData);
        bp.setcondition(stringData);
        v.push_back(bp);               // adding the object into the class
    }
       v.pop_back(); // since the last empty line is also added just pop it out
    
    stream.close();
    return true;
}


bool operator==(const book& lhs, const book& rhs){  // checking is ISBN, condition and language are all the same
        if (lhs.ISBN == rhs.ISBN &&
            lhs.condition == rhs.condition &&
            lhs.language == rhs.language){
                return true;
        }
            return false;
    }



bool operator>(const book& lhs, const book& rhs){  // operator to compare which book is greater
    if (lhs.ISBN > rhs.ISBN) {  
        return true;
    }

    else if(lhs.ISBN < rhs.ISBN){ 
        return false;
    }

    else if (lhs.ISBN == rhs.ISBN){  // if ISBN's are the same check the condition
        if (lhs.condition > rhs.condition) {
            return true;
        }
        else if(lhs.condition < rhs.condition){
            return false;
        }
        
        else if (lhs.condition == rhs.condition){  // if the conditions are also the same check the language
            if (lhs.language > rhs.language) {
            return true;
            }
            else if(lhs.language < rhs.language){
                return false;
            }
            else if(lhs.language == rhs.language){
                return false;
            }
        }
    }

    return false;
}

// good use for outputting the contents of the files

std::ostream &operator<<(std::ostream &output, std::vector<book> v) {
    for (unsigned int i = 0; i < v.size(); i++) {
        std::cout << v[i].getISBN() << ',' << v[i].getlanguage() << ',' << v[i].getcondition() << std::endl;
    }
    return output;
}



bool compare(book x, book y) {  // conparing which book is greater to sort the list backwards
        return (x > y);  
}


bool binarysearch(std::vector<book> list, std::vector<book> reqs, int current) {  // binary searching the book in the newbook list
    int hi = list.size()-1;;
    int low = 0;
    int mid;

    while (hi >= low) {
        mid = (hi + low)/2;

        if (reqs[current] == list[mid]) {   // if the current items are the same return true for a book found
            return true;
        } else if (reqs[current] > list[mid]) {  // if the book being searched is greater than the one being looked at on the list
            hi = mid-1;
        } else {
            low = mid+1;
        }
    }
    return false;
}

bool linearsearch(std::vector<book> list, std::vector<book> reqs, int current){ 
    for (unsigned int i = 0; i< list.size(); i++) { //itrating thru the newbooks
        if (reqs[current] == list[i]) { 
            return true;  // checking if the ith value on the list is equal to the current requested book
        }
    }
    return false;
}


void result(std::string filename, int foundBooks) {
    std::ofstream stream;
    stream.open(filename); // opening the file
    if (stream.fail()) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
    }
    stream << foundBooks << std::endl;
}



int main(int argc, char* argv[]) {


  if (argc != 4) {
    // error if not proper number of aruguments
    std::cerr << "Usage: ./SearchNewBooks <newbooks.dat> <request.dat> <result_file.dat>" << std::endl;  
    return 0;
  }
  
  if (std::string(argv[1]) != "newbooks.dat") {
    // if the file is not newbook.dat error message
    std::cerr << "Error: cannot open file " << argv[1] << std::endl;
    return 0;
  }
  
  if (std::string(argv[2]) != "request.dat") {
    // if the file is not request.dat error message
    std::cerr << "Error: cannot open file " << argv[2] << std::endl;
    return 0;
  }
    


    //making strings to store the arumengts into
    std::string newbookFile;
    std::string requestFile;
    std::string resultFile;



    newbookFile = argv[1];
    requestFile = argv[2];
    resultFile = argv[3];

    // vector of class book to store the newbooks and requests into
    std::vector<book>Newbook;
    std::vector<book>Requests;

    fileRead(newbookFile, Newbook);
    fileRead(requestFile, Requests);

    // making character for the sorting choice and int for number of found books
    char choice = 0;
    int numBooks = 0;

    std::cout << "Choice of search method ([l]inear, [b]inary)?" << std::endl;
    std::cin >> choice;
    while ((choice != 'b' && choice != 'l') || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignoring extra letters of a incorrect choice
        std::cerr << "Incorrect choice" << std::endl;
        std::cin >> choice;
    }
    std::chrono::high_resolution_clock::time_point start;  // defning the clock

    start = std::chrono::high_resolution_clock::now(); //starting the clock

if (choice == 'b'){
    std::sort(Newbook.begin(), Newbook.end(), compare); // extra parameter to sort in reverse
    for (unsigned int i = 0; i < Requests.size() ; i++) {
            if (binarysearch(Newbook, Requests, i)) {
                numBooks++; // incrementing the number of books if the binary search finds the ith book in the request list in the newbooks
            }
        }
}

else if(choice == 'l'){
    for (unsigned int i = 0; i< Requests.size(); i++) {
            if (linearsearch(Newbook, Requests, i)) {
                numBooks++;// incrementing the number of books if the linear search finds the ith book in the request list in the newbooks
            
            }
    }
}

    auto end = std::chrono::high_resolution_clock::now();  // ending the clock
    double elapsed_us = std::chrono::duration<double, std::micro>(end-start).count(); // difference in the starting and end timings
    std::cout << "CPU time: " << elapsed_us << " microseconds " << std::endl;
    result(resultFile, numBooks);  // writing the number of books into the result file
    return 0;
}
