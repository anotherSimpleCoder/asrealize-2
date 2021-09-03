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
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdio.h>
#include <png.h>
#include "asrPNG.h"

using namespace std;

asrPNG::asrPNG(string t, asrScreen* s){
	//internal init	

	title = t;
	filename = t + ".png";
	
	fp = fopen(filename.c_str(), "wb");
	
	screen = s;
	
	width = s->getResolution(ASR_WIDTH);
	height = s->getResolution(ASR_HEIGHT);

}

asrPNG::~asrPNG(){
	fclose(fp);
	png_destroy_write_struct(&png_ptr, &info_ptr);
}

int asrPNG::IOinit(){
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if(png_ptr == NULL){
		cerr << "Error when creating PNG struct" << endl;
		return -1;
	}

	info_ptr = png_create_info_struct(png_ptr);

	if(info_ptr == NULL){
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		cerr << "Error when creating PNG info struct" << endl;
		return -1;
	}
	
	if(setjmp(png_jmpbuf(png_ptr))){
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		cerr << "PNG Error!" << endl;
		return -1;
	}

	png_init_io(png_ptr, fp);

	return 0;
}

int asrPNG::fillInfo(){
	png_set_IHDR(png_ptr, info_ptr, width, height, 16, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	char* cTitle = new char[title.length() + 1];
	strcpy(cTitle, title.c_str());

	png_text title_text;
	title_text.compression = PNG_TEXT_COMPRESSION_NONE;
	title_text.key = "Title";
	title_text.text = cTitle;
	
	png_set_text(png_ptr, info_ptr, &title_text, 1);
	png_write_info(png_ptr, info_ptr);

	delete [] cTitle;
	return 0;
}

int asrPNG::writeImg(){
	png_bytep row = (png_bytep)malloc(sizeof(png_bytep) * width * 3);
	uint8_t r, g, b;

	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			asrPixel* p = screen->getPixel(x,y);
			asrColor* c = p->getColor();		
	
			r = c->getColor(ASR_RED);
			g = c->getColor(ASR_GREEN);
			b = c->getColor(ASR_BLUE);

			//cout << "(" << x << "," << y << ")" << ":" << "(" << (int)r << "," << (int)g << "," << (int)b << ")" << endl;

			row[(x)*3] = r;
			row[(x)*3+1] = g;
			row[(x)*3+2] = b;

		}
		png_write_row(png_ptr, row);
	}	

	png_write_end(png_ptr, info_ptr);

	return 0;
}
