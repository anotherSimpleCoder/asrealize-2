#include <iostream>
#include <fstream>
#include <vector>

#include "executer.h"


using namespace std;

void execute(executer* e, std::vector<entry> r, bool createPNG) {
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

		string varName = "";
		int varValue = 0;

		int end = 0; //String end
		int contentSize = 0;

		int x, y, red, green, blue, alpha = 0;
		string nameBuf = "";
		int amount = 0;

		int values[6];

		asrColor* color = NULL;
		asrVector* vector = NULL;

		if(r[4].content[0] == SEC_BODY) {
			for(int i = 5; i < size; i++) {
				e_buf = r[i];
				
				switch(e_buf.type) {
					case entryType::ASGN:
						varName = "";
						end = 0;
						
						contentSize = e_buf.content.size();

						if(e_buf.content[0] == ALPHABETIC) {
							varName = constructString(e_buf.content, 1, &end);
						}

						varValue = e_buf.content[end];
						
						if(e->variables.find(varName) == e->variables.end()){
							e->variables.insert(std::pair<string, int>(varName, varValue));
						}

						else {
							e->variables[varName] = varValue;
						}
					//	cout << varName << ":" << e->variables[varName] << endl;
						break;


					case entryType::COM:
						contentSize = e_buf.content.size();
					/*	
						cout << contentSize << endl;
						cout << endl;
						cout << endl;
					*/
						for(int j = 0; j < contentSize; j++) {
							//cout << "content:" << e_buf.content[j] << endl;
							//cout << endl;
							//cout << j << endl;
							//cout << endl;

							if(e_buf.content[j] == ALPHABETIC) {
								j += 1;
								nameBuf = constructString(e_buf.content, j, &end);
								//cout << nameBuf << endl;
								
								if(e->variables.find(nameBuf) != e->variables.end()) {
									varValue = e->variables[nameBuf];
								}
								//amount++;

								//cout << amount << ":" << nameBuf << ":" << varValue << endl;
								values[amount] = varValue;
								amount++;
								j = end-1;
							}

							else {
								//cout << amount << ":" << e_buf.content[j] << endl;
								values[amount] = e_buf.content[j];
								amount++;
							}
						}
/*
						for(int i = 0; i < amount; i++) {
							cout << i << ":" << values[i] << endl;
						}

*/
						x = values[0];
						y = values[1];
						red = values[2];
						green =  values[3];
						blue = values[4];
						alpha = values[5];

						vector = new asrVector(x,y);
						color  = new asrColor(red, green, blue, alpha);
						e->asrInstance->assign(color, vector);
						break;


					default:
						break;	
				}	
			}
		}

	}

	if(createPNG) {
		e->asrInstance->makePNG(title);
	}

	else {
		e->asrInstance->render();
	}
}


string constructString(std::vector<uint16_t> chars, int startPosition, int* endPosition) {
	int d = startPosition;
	string res = "";

	while(chars[d] != ALPHABETIC) {
		char c = (char)chars[d];
		res += c;
		d++;
	}

	d += 1;
	*endPosition = d;

	return res;
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
