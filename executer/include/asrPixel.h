#include "asrColor.h"
#include "asrVector.h"

class asrPixel{
private:
	asrColor* c;
	asrVector* v;

public:
	asrPixel(int x, int y);

	//getters
	asrColor* getColor();
	asrVector* getVector();

	//setters
	void setColor(int parameter, uint8_t value);
};
