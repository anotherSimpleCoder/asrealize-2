#include <iostream>
#include "asr.h"

using namespace std;

asr::asr(int w, int h){
	width = w;
	height = h;
	screen = new asrScreen(w, h);

	window = SDL_CreateWindow("asr-v2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if(window == NULL){
		cerr << "Window could not be created! (" << SDL_GetError() << ")" << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if(renderer == NULL){
		cerr << "Renderer could not be created (" << SDL_GetError() << ")" << endl;
	}
}

//getters
asrScreen* asr::getScreen(){
	return screen;
}

int asr::getResolution(int component){
	switch(component){
		case ASR_WIDTH:
			return width;

		case ASR_HEIGHT:
			return height;
	}

	return 1;
}

void asr::assign(asrColor* c, asrVector* v){
	int x, y;
	x = v->getPosition(ASR_X);
	y = v->getPosition(ASR_Y);

	screen->assign(c, x, y);	
}

void asr::render(){
	uint8_t r, g, b, a;
	SDL_Rect fillRect;
	SDL_Event e;
	bool quit = false;
	fillRect.w = 1;
	fillRect.h = 1;
	
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			asrPixel* p = screen->getPixel(x,y);
			asrColor* c = p->getColor();
			fillRect.x = x;
			fillRect.y = y;

			r = c->getColor(ASR_RED);
			g = c->getColor(ASR_GREEN);
			b = c->getColor(ASR_BLUE);
			a = c->getColor(ASR_ALPHA);

			//cout << "(" << x << "," << y << "): " << (int)r << "," << (int)g << "," << (int)b << "," << (int)a << endl;

			SDL_SetRenderDrawColor(renderer, r, g, b, a);
			SDL_RenderFillRect(renderer, &fillRect);
		}
	}

	SDL_RenderPresent(renderer);

	while(!quit){
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT){
				quit = true;
			}
		}	
	}
}

void asr::makePNG(string title){
	asrPNG* pngEngine = new asrPNG(title, screen);
	
	pngEngine->IOinit();
	pngEngine->fillInfo();
	pngEngine->writeImg();

	delete pngEngine;
}

asr::~asr(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
