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
