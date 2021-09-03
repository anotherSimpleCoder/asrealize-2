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
