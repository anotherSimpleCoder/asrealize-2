#include <vector>

struct binaryRegister {
	std::vector<uint16_t> reg;
};

typedef struct binaryRegister binaryRegister;

int process(binaryRegister* b);
