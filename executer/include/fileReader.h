#include <string>

#include "binaryRegister.h"

using namespace std;

struct fileReader {
	unsigned int* data;
	int dataSize; 
};


typedef struct fileReader fileReader;

int read(fileReader* f, string path);

int processValues(fileReader* f, binaryRegister* b);

