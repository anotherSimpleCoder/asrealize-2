#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "fileReader.h"

using namespace std;

int read(fileReader* f, string path) {
	streampos size;
	char* memblock;
	
	ifstream file(path, ios::in | ios::binary | ios::ate);
	
	if(!file.is_open()) {
		cerr << "Cannot open binary file!" << endl;
		return EXIT_FAILURE;
	}

	size = file.tellg();
	f->dataSize = size;
	memblock = new char[size];
	f->data = new unsigned int[size];	
	
	file.seekg(0, ios::beg);
	file.read(memblock, size);
	file.close();

	for(int i = 0; i < size; i++) {
		f->data[i] = (uint8_t)(memblock[i]);
		//cout << "0x" << std::hex << f->data[i] << endl;
	}

	delete memblock;
	return EXIT_SUCCESS;
}


int power(uint8_t b, uint8_t e) {
	uint16_t res = 1;
	
	for(int i = 0; i < e; i++) {
		res = res * b;
	}

	return res;
}

int processValues(fileReader* f, binaryRegister* b) {
	if(f == NULL) {
		cerr << "Empty memory!" << endl;
		return EXIT_FAILURE;
	}	

	int newSize = f->dataSize / 2;

	for(int i = 0; i < f->dataSize; i += 2) {
		uint8_t byte2 = f->data[i];
		uint8_t byte1 = f->data[i+1];
		uint16_t byteBuf = 0x0000;

		byteBuf += byte2;
		byteBuf = (byte1 * power(2,8)) + byteBuf;
		//cout << "0x" << std::hex << byteBuf << endl;
		b->reg.push_back(byteBuf);
	}

	return EXIT_SUCCESS;
}

