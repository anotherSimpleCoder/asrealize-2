#include <iostream>
#include <vector>

#include "binaryRegister.h"

using namespace std;

void processValues(binaryRegister* b, std::vector<entry>* regBuf) {
	std::vector<entry> entryRegister;

	int size = b->reg.size();

	bool isMeta = false;
	bool isBody = false;

	bool isWidth = false;
	bool isHeight = false;
	bool isTitle = false;

	bool isAssign = true;
	bool isCommand = true;
	bool isAlpha = true;

	entry height;
	entry width;
	entry title;
	entry e;

	for(int i = 0; i < size; i++) {
		int entry = b->reg[i];

		switch(entry) {
			case SEC_META:
				isMeta = true;
				break;

			case ATTR_HEIGHT:
				if(isMeta) {
					if(isHeight) {
						height.type = entryType::ATTR;
						isHeight = false;
					}
					
					else {
						isHeight = true;
					}
				}
				break;

			case ATTR_WIDTH:
				if(isMeta) {
					if(!isHeight) {
						if(isWidth) {
							width.type = entryType::ATTR;
							isWidth = false;
						}

						else {
							isWidth = true;
						}
					}
				}
				break;

			case ATTR_TITLE:
				if(isMeta) {
					if(isTitle) {
						title.type = entryType::ATTR;
						isTitle = false;
					}

					else {
						isTitle = true;
					}
				}
				break;

			case SEC_BODY:
				if(isMeta) {
					e.type = entryType::SEC;
					e.content.push_back(SEC_META);
					entryRegister.push_back(e);
					entryRegister.push_back(height);
					entryRegister.push_back(width);
					entryRegister.push_back(title);
					isMeta = false;
					isBody = true;
					e.type = entryType::SEC;
					e.content.push_back(SEC_BODY);
					entryRegister.push_back(e);		
				}
				break;

			case ASSIGN:
				if(isBody) {
					if(!isAssign) {
						isAssign = true;
						e.type = entryType::ASGN;
					}

					else {
						isAssign = false;
						entryRegister.push_back(e);
					}
				}
				break;

			case ALPHABETIC:
				if(isAlpha) {
					isAlpha = false;
				}

				else {
					isAlpha = true;
				}
				break;

			case COMM:
				if(isBody) {
					if(isCommand) {
						entryRegister.push_back(e);
						isCommand = false;
					}

					else{
						isCommand = true;
						e.type = entryType::COM;
					}
				}

			default:
				if(isMeta) {
					if(isHeight) {
						height.content.push_back(entry);
					}

					if(isWidth) {
						width.content.push_back(entry);
					}

					if(isTitle) {
						title.content.push_back(entry);
					}
				}

				if(isBody) {
					if(isAlpha) {
						e.content.push_back(ALPHABETIC);
						e.content.push_back(entry);
					}

					else {
						e.content.push_back(entry);
					}
				}
		}
	}

	regBuf = &entryRegister;
}

void printContentToTokens(binaryRegister* b) {
	int size = b->reg.size();

	for(int i = 0; i < size; i++) {
		int entry = b->reg[i];

		switch(entry) {
			case SEC_META:
				cout << "meta" << endl;
				break;

			case SEC_BODY:
				cout << "body" << endl;
				break;
			
			case ATTR_HEIGHT:
				cout << "height" << endl;
				break;

			case ATTR_WIDTH:
				cout << "width" << endl;
				break;

			case ATTR_TITLE:
				cout << "title" << endl;
				break;

			case ASSIGN:
				cout << "assign" << endl;
				break;

			case COMM:
				cout << "command" << endl;
				break;

			case ALPHABETIC:
				cout << "alphabetic" << endl;
				break;

			case NUL:
				cout << endl;
				break;

			default:
				cout << entry << endl;
		}
	}
}

void printRegisterContent(binaryRegister* b) {
	int size = b->reg.size();

	for(int i = 0; i < size; i++) {
		cout << b->reg[i] << endl;
	}
}
