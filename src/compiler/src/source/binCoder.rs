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
use super::entryType::EntryType;
use super::entry::Entry;
use super::binCodes;
use std::collections::LinkedList;
use std::fmt;

pub struct BinCoder{
	pub data: Vec<u16>
}

fn printType<T>(_: &T) {
	println!("{}", std::any::type_name::<T>());
}

fn asciiExtract(s: &String) -> LinkedList<u16> {
	let mut res: LinkedList<u16> = LinkedList::new();
	let size = s.len();

	for i in 0..size {
		let c = s.chars().nth(i).unwrap() as u16;
		assert!(c < 128);
		res.push_back(c);
		//println!("{:#06x}", c);
	}

	return res;
}

fn numExtract(s: &String) -> LinkedList<u16> {
//	println!("called");
	let mut res: LinkedList<u16> = LinkedList::new();
	let size = s.len();
	let mut buff = 0;

	for i in 0..size {
		let c = s.chars().nth(i).unwrap().to_digit(10).unwrap() as u16;
		//println!("{}", c);

		buff = (buff*10) + c;
		//res.push_back(c);
		//println!("{:#06x}", c);
	} 

	//println!("{}", buff);
	res.push_back(buff);

	return res;
}

fn isAlphabetic(s: &String) -> bool{
	let d = s.chars().nth(0).unwrap().is_alphabetic();
	return d;	
}

fn isNumeric(s: &String) -> bool {
	let d = s.chars().nth(0).unwrap().is_numeric();
	return d;
}

impl BinCoder {
	pub fn writeData(&mut self, entries: &LinkedList<Entry>) {
		let mut isMeta = false;
		let mut isBody = false;

		let mut isHeight = false;
		let mut isWidth = false;
		let mut isTitle = false;

		let mut isCommand = false;
		let mut isAssign = false;
		let mut wasNul = false;

		for i in entries.iter() {	
			match i.kind {
				EntryType::SECTION => {	
					match i.content[0].as_str() {
						"meta" => {
							isMeta = true;
							self.data.push(binCodes::SEC_META);
							//println!("{:#04x}", binCodes::SEC_META);
						},

						"body" => {
							if isMeta && isTitle{
								//println!("{:#04x}", binCodes::ATTR_TITLE);
								//println!("{:#04x}", binCodes::NUL);
								self.data.push(binCodes::ATTR_TITLE);
								self.data.push(binCodes::NUL);
								isMeta = false;
								isTitle = false;
								//println!("{:#04x}", binCodes::SEC_BODY);
								self.data.push(binCodes::SEC_BODY);
								isBody = true;
							}

							else{
								panic!("Meta section was never stated or title is missing!");
							}
						},
						_ => panic!("Invalid section definition!")
					}
				},

				EntryType::ATTR => {
					if isMeta {
						let value = &(i.content[1]);
						match i.content[0].as_str() {
							"height" => {
								//let value = &(i.content[1]);
								isHeight = true;
								//println!("{:#04x}", binCodes::ATTR_HEIGHT);
								self.data.push(binCodes::ATTR_HEIGHT);
		
								if isNumeric(value) {
									let d = numExtract(value);
									self.addValue(d);	
								}

								else {
									panic!("Only numeric values for height attribute");
								}
							},

							"width" => {
								if isHeight {
									//println!("{:#04x}", binCodes::ATTR_HEIGHT);
									self.data.push(binCodes::ATTR_HEIGHT);
									isHeight = false;
									isWidth = true;
									//println!("{:#04x}", binCodes::ATTR_WIDTH);
									self.data.push(binCodes::ATTR_WIDTH);

									if isNumeric(value) {
										let d = numExtract(value);
										self.addValue(d);
									}

									else {
										panic!("Only numeric values for width attribute");
									}
								}

								else {
									panic!("Height not given!");
								}
							},

							"title" => {
								if isWidth && !isHeight {
									//println!("{:#04x}", binCodes::ATTR_WIDTH);
									self.data.push(binCodes::ATTR_WIDTH);
									isWidth = false;
									isTitle = true;
									//println!("{:#04x}", binCodes::ATTR_TITLE);
									self.data.push(binCodes::ATTR_TITLE);
									//println!("{}", value);
									let d = asciiExtract(value);
									self.addValue(d);
								}

								else {
									panic!("Only one resolution attribute given!");
								}
							},


							_ => panic!("Invalid attribute!")
						}
					}

					else {
						panic!("No Meta section found!");
					}
				},

				EntryType::ASSIGN => {
					if isBody && !isMeta && !isCommand {
						isAssign = true;
						let name = &i.content[0];
						//println!("{:#04x}", binCodes::ASSIGN);
						self.data.push(binCodes::ASSIGN);						

						if isAlphabetic(name) {
							//println!("{:#04x}", binCodes::ALPHABETIC);
							self.data.push(binCodes::ALPHABETIC);
							let d = asciiExtract(name);
							self.addValue(d);
							//println!("{:#04x}", binCodes::ALPHABETIC);
							self.data.push(binCodes::ALPHABETIC);
						}

						else {
							panic!("Variables need to start with a letter!");
						}

						//println!("{}", i.content[0]);
						//println!("{:#04x}", binCodes::NUL);
						
						if isNumeric(&i.content[1]) {
							let d = numExtract(&i.content[1]);
							self.addValue(d);
						}						
	
						else if isAlphabetic(&i.content[1]) {
							self.data.push(binCodes::ALPHABETIC);
							let d = asciiExtract(&i.content[1]);
							self.addValue(d);
						}

						//println!("{:#04x}", i.content[1]);
						//println!("{:#04x}", binCodes::ASSIGN);
						self.data.push(binCodes::ASSIGN);
						isAssign = false;
					}
					
					else {
						panic!("Cannot do assign outside of body section");
					}
				},

				EntryType::COMMAND => {
					if isBody && !isMeta && !isAssign {
						isCommand = true;
						//println!("{:#04x}", binCodes::COMM);
						self.data.push(binCodes::COMM);

						let size = i.content.len();

						for j in 0..size {
							if isAlphabetic(&i.content[j]) {
								//println!("{:#04x}", binCodes::ALPHABETIC);
								self.data.push(binCodes::ALPHABETIC);
								let d = asciiExtract(&i.content[j]);
								self.addValue(d);
								//println!("{:#04x}", binCodes::ALPHABETIC);
								self.data.push(binCodes::ALPHABETIC);
							}

							else if isNumeric(&i.content[j]){
								let d = numExtract(&i.content[j]);
								self.addValue(d);
							}
						}

						/*
						println!("{}", i.content[0]); //x
						println!("{}", i.content[1]); //y
						println!("{}", i.content[2]); //r
						println!("{}", i.content[3]); //g
						println!("{}", i.content[4]); //b
						println!("{}", i.content[5]); //a
						*/
						//println!("{:#04x}", binCodes::COMM);
						self.data.push(binCodes::COMM);
						isCommand = false;
					}

					else {
						panic!("Cannot do commands outside of body section");
					}	
				},	

				EntryType::NUL => if !isMeta && isBody {
					//println!("{:#04x}", binCodes::NUL);
					self.data.push(binCodes::NUL);
				},

				_ => println!("yet to be implemented..")

			}
		}
	}

	fn addValue(&mut self, d: LinkedList<u16>) {
		for i in d.iter() {
			let x = *i;
			self.data.push(x);
		}
	}
}
