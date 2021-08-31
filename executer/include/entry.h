#include "entryType.h"

using namespace std;

//TODO: Stilltodo
struct entry {
	entryType type;
	std::vector<uint16_t> content;
};

typedef struct entry entry;
