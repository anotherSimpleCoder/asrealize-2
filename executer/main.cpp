#include <iostream>
#include <fstream>

#include "executer.h"

using namespace std;

int main(int argc, char** argv) {
	bool makePNG = false;
	string path = "";
	string option = "";

	if(argc == 1) {
		cerr << "Insufficient arguments!" << endl;	
		return EXIT_FAILURE;
	}
	
	path = argv[1];

	if(argc == 3) {
		option = argv[2];
		option.compare("-png");
		makePNG = true;
	}

	fileReader f = {NULL};
	binaryRegister b;
	executer e;	
//	std::vector<entry> reg;

	read(&f, path);
	processValues(&f, &b);


//	printRegisterContent(&b);
//	printContentToTokens(&b);	
	std::vector<entry> reg = processValues(&b);	
//	printRegister(reg);
	execute(&e, reg, makePNG);
	
	return EXIT_SUCCESS;	
}
