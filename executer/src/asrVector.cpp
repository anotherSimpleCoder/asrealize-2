#include <iostream>
#include "asrVector.h"
#include "asrDefines.h"

using namespace std;

asrVector::asrVector(int pX, int pY){
	x = pX;
	y = pY;
}

int asrVector::getPosition(int component){
	switch(component){
		case ASR_X:
			return x;

		case ASR_Y:
			return y;
	}

	return 1;
}

void asrVector::setPosition(int component, int value){
	switch(component){
		case ASR_X:
			x = value;
			break;

		case ASR_Y:
			y = value;
			break;
	}
}
