#include <iostream>
#include <fstream>

#include "executer.h"

using namespace std;

int main(int argc, char** argv) {
	fileReader f = {NULL};
	binaryRegister b;	
//	std::vector<entry> reg;

	read(&f, "test.asb");
	processValues(&f, &b);


//	printRegisterContent(&b);
	printContentToTokens(&b);	
	std::vector<entry> reg = processValues(&b);	
//	printRegister(reg);

	
	return EXIT_SUCCESS;	
}
