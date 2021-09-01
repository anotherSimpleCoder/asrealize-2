#include <vector>

#include "binCodes.h"
#include "entry.h"

struct binaryRegister {
	std::vector<uint16_t> reg;
};

typedef struct binaryRegister binaryRegister;

void printRegisterContent(binaryRegister* b);
void printContentToTokens(binaryRegister* b);
std::vector<entry> processValues(binaryRegister* b);
