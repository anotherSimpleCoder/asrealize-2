#include <iostream>
#include "asrColor.h"
#include "asrDefines.h"

using namespace std;

asrColor::asrColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	red = r;
	green = g;
	blue = b;
	alpha = a;
}


//getters
uint8_t asrColor::getColor(int component){
	switch(component){
		case ASR_RED:
			return red;
		
		case ASR_GREEN:
			return green;

		case ASR_BLUE:
			return blue;

		case ASR_ALPHA:
			return alpha;
	}

	return 1;
}

//setters
void asrColor::setColors(int color, uint8_t value){
	switch(color){
		case ASR_RED:
			red = value;
			break;

		case ASR_GREEN:
			green = value;
			break;

		case ASR_BLUE:
			blue = value;
			break;

		case ASR_ALPHA:
			alpha = value;
			break;
	}
}
