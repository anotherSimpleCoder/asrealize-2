#include <vector>
#include "asr.h"
#include "fileReader.h"

struct executer {
	asr* asrInstance;
};

typedef struct executer executer;

void printRegister(std::vector<entry> r);
void execute(executer* e, std::vector<entry> r);
