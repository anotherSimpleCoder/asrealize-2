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
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv) {
	if(argc == 1) {
		cerr << "Insufficient arguments!" << endl;
		return 1;
	}

	string filePath = argv[1];
	bool makePNG = false;

	if(argc == 3) {
		//cout << argv[2] << endl;
		string png = "-png";
		string arg3 = argv[2];		

		if(arg3 == "-png") {
			makePNG = true;
		}
	}

	int size = filePath.length();
	string fileName = "";

	//cout << filePath << endl;

	for(int i = 0; i < (size-4); i++) {
		fileName += filePath[i];
	}

//	cout << fileName << endl;

	fileName += ".asb";

	string compilerCall =  "asrealize2-compiler " + filePath + " " + fileName;
	compilerCall = "./" + compilerCall;

	//cout << compilerCall << endl;

	system(compilerCall.c_str());

	string execCall = "";
	if(makePNG) {
		execCall = "asrealize2-executer " + fileName + " -png";
	}

	else {
		execCall = "asrealize2-executer " + fileName;
	}

	execCall = "./" + execCall;
	//cout << makePNG << endl;
	//cout << execCall << endl;

	system(execCall.c_str());
	return 0;
}
