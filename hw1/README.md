# 36C-1
## Objectives of the assignment 
The objectives of this programming assignment are: 

● Reviewing most of the concepts learned in ECS 36a and ECS 36b (object-oriented 
programming, file manipulation, command line arguments, operator overloading, 
Makefile, etc.) 

● Understanding how computational complexity can apply to real-life programs. 

● Running test measurements and analysing the results in order to provide an argued 
answer to the given problem. 

● Writing high-quality C++ code by following established industry standards. 

## Program description 
### Introduction 

You are helping the library catalog books, and provide books to departments upon request.. 
The librarian received new shipments of books. The books are identified with an ISBN number, language, "english","french", "chinese","spanish” and ​type:​ “new”, “used”, digital.  
They also receive requests for books with different  ISBN numbers, languages  in either new, used, or digital format. (​ISBN: this is the number the publisher assigns ​An ISBN is assigned to each edition 
and variation of a book)  
 
For example the Library may receive a shipment of 5 books   

```
$ cat newbooks.dat 
 
$cat request.dat
```
### Programing Assignment: 

Create a program SearchNewBooks.cc that given as command line input  newbooks.dat and request.dat and a method of search either binary or linear, creates a file of the number of books found from the request list 
``` $SearchNewBooks  newbooks.dat request.dat  //run program 
$Choice of search method ([l]inear, [b]inary)? 
1 
CPU time: 10.777 microseconds 
 
$cat found.dat 
1
```
