#include <png.h>
#include "asrScreen.h"

using namespace std;

class asrPNG{
private:
	FILE* fp;
	string title;
	string filename;	//title+".png"
	png_structp png_ptr;
	png_infop info_ptr;
	asrScreen* screen;
	int width;		//will be extracted from asrScreen
	int height;		//will be extracted from asrScreen

public:	
	//constructor + destructor
	asrPNG(string t, asrScreen* s);
	~asrPNG();

	int IOinit();
	int fillInfo();
	int writeImg();

};
