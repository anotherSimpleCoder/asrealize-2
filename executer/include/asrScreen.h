#include "asrPixel.h" 
#include "asrDefines.h"

class asrScreen{
private:
	int width;
	int height;
	asrPixel*** pixelMap;

public:
	asrScreen(int w, int h);

	int getResolution(int component);
	asrPixel* getPixel(int x, int y);

	void setResolution(int component, int value);
	void assign(asrColor* c, int x, int y);

};
