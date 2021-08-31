#include <iostream>
#include <fstream>

#include "fileReader.h"

using namespace std;

int main(int argc, char** argv) {
	fileReader f = {NULL};
	binaryRegister b;	

	read(&f, "test.asb");
	processValues(&f, &b);


	process(&b);
	
	return EXIT_SUCCESS;	
}
