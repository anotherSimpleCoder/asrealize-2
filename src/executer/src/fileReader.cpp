/*
Copyright (c) 2021 anotherSimpleCoder. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software must display the following acknowledgement:
This product includes software developed by "anotherSimpleCoder".

4. Neither the name of the copyright holder ("anotherSimpleCoder")  nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY ANOTHERSIMPLECOER "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ANOTHERSIMPLECODER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*/
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

