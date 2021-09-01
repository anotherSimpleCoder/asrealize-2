#include <iostream>
#include "asrPixel.h"
#include "asrDefines.h"

using namespace std;

asrPixel::asrPixel(int x, int y){
	c = new asrColor(0, 0, 0, 0);
	v = new asrVector(x, y);
}

//getters
asrColor* asrPixel::getColor(){
	return c;
}

asrVector* asrPixel::getVector(){
	return v;
}

//setters
void asrPixel::setColor(int parameter, uint8_t value){

	switch(parameter){
		case ASR_RED:
			c->setColors(ASR_RED, value);
			break;

		case ASR_GREEN:
			c->setColors(ASR_GREEN, value);
			break;

		case ASR_BLUE:
			c->setColors(ASR_BLUE, value);
			break;

		case ASR_ALPHA:
			c->setColors(ASR_ALPHA, value);
			break;
	}		
}
