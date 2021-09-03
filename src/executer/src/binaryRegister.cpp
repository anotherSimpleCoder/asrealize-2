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
#include <vector>

#include "binaryRegister.h"

using namespace std;

std::vector<entry> processValues(binaryRegister* b) {
	std::vector<entry> entryRegister;

	int size = b->reg.size();

	bool isMeta = false;
	bool isBody = false;

	bool isWidth = false;
	bool isHeight = false;
	bool isTitle = false;

	bool isAssign = false;
	bool isCommand = false;
	bool isAlpha = false;

	entry height;
	entry width;
	entry title;
	entry e;

	for(int i = 0; i < size; i++) {
		int entry = b->reg[i];

		switch(entry) {
			case SEC_META:
				if(!isMeta) {
					isMeta = true;
					e.type = entryType::SEC;
					e.content.push_back(SEC_META);
					entryRegister.push_back(e);
					e.content.clear();
					break;
				}



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
					entryRegister.push_back(height);
					entryRegister.push_back(width);
					entryRegister.push_back(title);
					isMeta = false;
					isBody = true;
					e.type = entryType::SEC;
					e.content.push_back(SEC_BODY);
					entryRegister.push_back(e);
					e.content.clear();		
				}
				break;

			case ASSIGN:
				if(isBody) {
					if(!isAssign) {
						e.content.clear();
						isAssign = true;
						e.type = entryType::ASGN;
						break;
					}

					else {
						isAssign = false;
						entryRegister.push_back(e);
						break;
					}
				}
				//break;

			case ALPHABETIC:
				if(isAlpha) {
					e.content.push_back(ALPHABETIC);
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
						break;
					}

					else{
						e.content.clear();
						isCommand = true;
						e.type = entryType::COM;
						break;
					}
				}

			case NUL:
				break;

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
				break;
		}
	}

	return entryRegister;
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
		cout << std::hex << b->reg[i] << endl;
	}
}
