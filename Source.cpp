#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <string.h>

#include "libs\hash_list.h"
#include "libs\hash_hash.h"

#define SIZE_HASH 10000

int main(int argc, char * argv[]) {
	hash_hash hash_hash_instance(SIZE_HASH);
	hash_list hash_list_instance(SIZE_HASH);
	std::string line;
	std::ifstream myFile(argv[1]);	// input file

	char* temp;
	int word_len;
	
	if (myFile.is_open())
		while (getline(myFile, line)) {
			word_len = (int) line.length();
			temp = new char[word_len];
			strcpy(temp, line.c_str());
			hash_hash_instance.add(temp);
			hash_list_instance.add(temp);
		}
	else
		std::cout << "unable to open file\n";

	std::cout << "all elements inserted\n\n";
	myFile.close();
	myFile.open(argv[2]);									// test file
	std::ofstream myResultFile(argv[3], std::ios::app);		// result file

	std::clock_t start;
	double duration;

	if (myFile.is_open())
		while (getline(myFile, line)) {
			start = std::clock();
			temp = hash_list_instance.get((char*)line.c_str());
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

			if (!temp)
				myResultFile << "[HASH_LIST] tempo: " << duration << " ms - " << line << " - element not found\n";
			else
				myResultFile << "[HASH_LIST] tempo: " << duration << " ms - " << temp << '\n';

			start = std::clock();
			temp = hash_hash_instance.get((char*)line.c_str());
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

			if (!temp)
				myResultFile << "[HASH_HASH] tempo: " << duration << " ms - " << line << " - element not found\n";
			else
				myResultFile << "[HASH_HASH] tempo: " << duration << " ms - " << temp << '\n';
		}
	else {
		std::cout << "unable to open test file\n";
		return 0;
	}

	myFile.close();
	myResultFile.close();
	
	system("pause");
	return 0;
}