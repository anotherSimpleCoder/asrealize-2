#include "entryType.h"

using namespace std;

struct entry {
	entryType type;
	std::vector<uint16_t> content;
};

typedef struct entry entry;
