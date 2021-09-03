#include <iostream>
#include "asrScreen.h"


using namespace std;

asrScreen::asrScreen(int w, int h){
	width = w;
	height = h;

	pixelMap = new asrPixel**[width];

	for(int x = 0; x < width; x++){
		pixelMap[x] = new asrPixel*[height];
	}

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			pixelMap[x][y] = new asrPixel(x, y);
			//cout << "x:" << x << "," << " y:" << y << endl;
		}
	}
}

//getter
int asrScreen::getResolution(int component){
	switch(component){
		case ASR_WIDTH:
			return width;
			
		case ASR_HEIGHT:
			return height;
	}

	return 0;
}

asrPixel* asrScreen::getPixel(int x, int y){
	return pixelMap[x][y];
}


//setters
void asrScreen::setResolution(int component, int value){
	switch(component){
		case ASR_WIDTH:
			width = value;
			return;

		case ASR_HEIGHT:
			height = value;
			return;
	}
}

void asrScreen::assign(asrColor* c, int x, int y){
	asrPixel* p = pixelMap[x][y];
	

	p->setColor(ASR_RED, c->getColor(ASR_RED));
	p->setColor(ASR_GREEN, c->getColor(ASR_GREEN));
	p->setColor(ASR_BLUE, c->getColor(ASR_BLUE));
	p->setColor(ASR_ALPHA, c->getColor(ASR_ALPHA));
}
