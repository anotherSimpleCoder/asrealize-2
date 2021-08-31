#include <iostream>
#include <vector>

#include "binCodes.h"
#include "binaryRegister.h"

using namespace std;

//TODO: Have fun with dis boi hehe
int process(binaryRegister* b) {
	bool isMeta = false;
	bool isBody = false;
	
	bool isHeight = false;
	bool isWidth = false;
	bool isTitle = false;

	bool isAlphabetic = false;

	int heightBuf = 0;
	int widthBuf = 0;
	string titleBuf = "";

	for(int i = 0; i < b->reg.size(); i++) {
		uint16_t entry = b->reg[i];

		switch(entry) {
			//Sections
			case SEC_META:
				isMeta = true;
				cout << "META" << endl;
				break;				

			case SEC_BODY:
				if(isMeta) {
					isMeta = false;
					isBody = true;					
					cout << "BODY" << endl;
					break;
				}

				else {
					cerr << "No meta section found!" << endl;
					return 1;
				}


			//Attributes
			case ATTR_HEIGHT:
				if(isMeta) {
					if(isHeight && heightBuf != 0) {
						isHeight = false;
						break;
					}

					else {

						isHeight = true;
						cout << "ATTR_HEIGHT" << endl;
						break;

					}
				}

				else {
					cerr << "No attributes outside of meta!" << endl;
					return 1;
				}

			case ATTR_WIDTH:
				if(isMeta) {
					if(isWidth && widthBuf != 0) {
						isWidth = false;
						break;
					}

					else {
						isWidth = true;
						cout << "ATTR_WIDTH" << endl;
						break;
					}
				}

				else {
					cerr << "No attributes outside of meta!" << endl;
					return 1;
				}

			case ATTR_TITLE:
				if(isMeta) {
					if(isTitle && titleBuf != "") {
						cout << titleBuf << endl;
						isTitle = false;
						break;			
					}					

					else {
						isTitle = true;
						cout << "ATTR_TITLE" << endl;
						break;
					}
				}

				else {
					cerr << "No attributes outside of meta!" << endl;
					return 1;
				}
		
			//Assign
			case ASSIGN:
				if(isBody){
					cout << "ASSIGN" << endl;
					break;
				}

				else {
					cerr << "No commands outside of body!" << endl;
					return 1;
				}			

			//Com
			case COMM:
				if(isBody) { 
					cout << "COMM" << endl;
					break;	
				}

				else {
					cerr << "No commands outside of body" << endl;
					return 1;
				}

			//NUl
			case NUL:
				cout << "NUL" << endl;
				break;

			//Alphabetic
			case ALPHABETIC:
				//cout << isAlphabetic << endl;
				if(isAlphabetic) {
					isAlphabetic = false;
					//cout << "ALPHABETIC" << endl;
					break;
				}
			
				else {	
					isAlphabetic = true;
					//cout << "ALPHABETIC" << endl;
					//cout << "ok" << endl;
					break;
				}


			default:
				//cout << isAlphabetic << endl;
				if(isAlphabetic || isTitle) {
					char c = (char)(entry);
					
					if(isTitle) {
						titleBuf += c;
					}

					//cout << entry << endl;
					else {
						cout << c << endl;
					}
				}

				else if (!isAlphabetic){
					cout << entry << endl;

					if(isWidth) {
						widthBuf = entry;
					}

					else if(isHeight) {
						heightBuf = entry;
					}
				}
				//cout << entry << endl;	
		}
	}


	return 0;
}
