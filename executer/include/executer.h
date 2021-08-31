#include <vector>
#include <unordered_map>
#include <string>
#include "asr.h"
#include "fileReader.h"


struct executer {
	asr* asrInstance;
	std::unordered_map<std::string, int> variables;
};

typedef struct executer executer;

void printRegister(std::vector<entry> r);
void execute(executer* e, std::vector<entry> r);
string constructString(std::vector<uint16_t> chars, int startPosition, int* endPosition);
