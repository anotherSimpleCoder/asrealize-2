#include <SDL.h>
#include "asrPNG.h"

class asr{
private:
	int width;
	int height;
	asrScreen* screen;

	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	asr(int w, int h);
	~asr();	

	//getters
	int getResolution(int component);
	asrScreen* getScreen();

	void assign(asrColor* c, asrVector* v);
	void render();
	void makePNG(string title);	
};
