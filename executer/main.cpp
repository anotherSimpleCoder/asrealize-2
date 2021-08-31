#include <iostream>
#include <fstream>

#include "fileReader.h"

using namespace std;

int main(int argc, char** argv) {
	fileReader f = {NULL};
	binaryRegister b;	
	std::vector<entry> reg;

	read(&f, "test.asb");
	processValues(&f, &b);


//	printRegister(&b);
//	printContentToTokens(&b);	
	processValues(&b, &reg);	
	
	return EXIT_SUCCESS;	
}
