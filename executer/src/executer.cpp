#include <iostream>
#include <fstream>
#include <vector>

#include "executer.h"

using namespace std;

void execute(executer* e, std::vector<entry> r) {
//	const entry meta = {entryType::SEC, SEC_META};
//	const entry body = {entryType::SEC, SEC_BODY};
//	const entry alpha = {entryType::SEC, SEC_BODY};

	int width = 0;
	int height = 0;
	string title = "";

	int size = r.size();
	entry e_buf;

	if(r[0].content[0] == SEC_META) {
		height = r[1].content[0];
		width = r[2].content[0];

		int length = r[3].content.size();
		//cout << length;
		for(int i = 0; i < length; i++) {
			char c = r[3].content[i];
			title += c;
		}

		e->asrInstance = new asr(width, height);
		cout << title << endl;	
	}
}

void printRegister(std::vector<entry> r) {
	int size = r.size();

//	cout << size << endl;
	
	for(int i = 0; i < size; i++) {
		entry* e = &(r[i]);
		std::vector<uint16_t> content = e->content;

		int conSize = content.size();


		for(int j = 0; j < conSize; j++) {
			//cout << "check" << endl; 
//			cout << "works" << endl;
			cout << std::hex << content[j] << endl;
		}
	}
}
