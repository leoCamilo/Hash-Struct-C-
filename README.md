# Hash-Struct-C++
A c++ implementation of a hash map struct

this project contains three structs:
  1. [wordlist](/libs/word_list.cpp) is a list implementation with binary search and sort insertion
  2. [hash-list](/libs/hash_list.cpp) is a hash struct that use list to collision control
  3. [hash-hash](/libs/hash_hash.cpp) is a hash struct that use hash to collision control
  
To execute the program:
  "file.exe" [arg 1] [arg 2] [arg 3]
  
  - [arg 1] - insertion file, that contains the data
  - [arg 2] - test file, contais the search words
  - [arg 3] - out file, with results
  
example: "Hash Project.exe" data/input.txt data/test.txt data/results.txt
