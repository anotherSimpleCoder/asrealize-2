#include <vector>

#include "binCodes.h"
#include "entry.h"

struct binaryRegister {
	std::vector<uint16_t> reg;
};

typedef struct binaryRegister binaryRegister;

void printRegister(binaryRegister* b);
void printContentToTokens(binaryRegister* b);
void processValues(binaryRegister* b, std::vector<entry>* regBuf);
