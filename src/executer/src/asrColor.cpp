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
