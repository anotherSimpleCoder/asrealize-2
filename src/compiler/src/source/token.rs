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
pub enum Token{
	//non parametric
	HASH,	//#
	DASH,	//-
	OB,	//(
	CB,	//)
	COM, 	//,
	COL,	//:
	QT,	//'
	SPACE,	//"
	NWLINE,	//\n
	NUL,	//invalid

	//parametric
	LT(String),
	DIG(String)
}

impl Token{
	pub fn printToken(&self){
		match self{
			Token::HASH => println!("HASH"),
			Token::DASH => println!("DASH"),
			Token::OB => println!("OB"),
			Token::CB => println!("CB"),
			Token::COM => println!("COM"),
			Token::COL => println!("COL"),
			Token::QT => println!("QT"),
			Token::SPACE => println!("SPACE"),
			Token::NWLINE => println!("NWLINE"),
			Token::NUL => println!("NUL"),

			Token::LT(x) => println!("LT({})", x),
			Token::DIG(x) => println!("DIG({})", x)
		}
	}


	pub fn compare(&self, t: Token) -> bool{
		match self {
			Token::HASH => {
				match t {
					Token::HASH => return true,
					_ => return false
				}
			},

			Token::DASH => {
				match t {
					Token::DASH => return true,
					_ => return false
				}
			},

			Token::OB => {
				match t {
					Token::OB => return true,
					_ => return false
				}
			},

			Token::CB => {
				match t {
					Token::CB => return true,
					_ => return false
				}
			},

			Token::COM => {
				match t {
					Token::COM => return true,
					_ => return false
				}
			},

			Token::COL => {
				match t {
					Token::COL => return true,
					_ => return false
				}
			},

			Token::QT => {
				match t {
					Token::QT => return true,
					_ => return false
				}
			},

			Token::SPACE => {
				match t {
					Token::SPACE => return true,
					_ => return false
				}
			},

			Token::NWLINE => {
				match t {
					Token::NWLINE => return true,
					_ => return false
				}
			},

			Token::NUL => {
				match t {
					Token::NUL => return true,
					_ => return false
				}
			},

			Token::LT(x) => {
				match t {
					Token::LT(y) => {
						if x == &y {
							return true;
						}

						return false;
					},
					_ => return false
				}
			},

			Token::DIG(x) => {
				match t {
					Token::DIG(y) => {
						if x == &y {
							return true;
						}

						return false;
					},
					_ => return false
				}
			}
		}
	}
}
