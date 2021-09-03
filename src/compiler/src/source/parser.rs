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
use super::token::Token;
use super::entry::Entry;
use super::entryType::EntryType;
use std::collections::LinkedList;

pub struct Parser{
	pub entryRegister: LinkedList<Entry>
}

impl Parser {
	pub fn parse(&self, tokenList: &LinkedList<Token>) -> Entry {
		let mut c: Vec<String> = Vec::new();
		let mut e: Entry;

		//Switches
		let mut isSection = false;
		let mut isAttribute = false;
		let mut isCommand = false;
		let mut isAssignment = false;

		let mut wasLt = false;		
		let mut wasDig = false;

		let mut bracketOpened = false;
		let mut bracketClosed = false;
		
		let mut qtOpened = false;
		let mut qtClosed = false;
	
		//Buffer
		let mut wordBuf = String::new();
		let mut numBuf = String::new();
		let mut typeBuf: EntryType = EntryType::NUL;
	
		for i in tokenList.iter() {
			//i.printToken();
			match i{
				Token::HASH => isSection = true,
				Token::DASH => isAttribute = true,
				Token::OB => bracketOpened = true,

				Token::CB => {
					if bracketOpened {
						if wasDig {
							c.push(numBuf);
							numBuf = String::new();
							wasDig = false;
						}

						if wasLt {
							c.push(wordBuf);
							wordBuf = String::new();
							wasLt = false;
						}

						bracketOpened = false;
						bracketClosed = true;
					}

					else {
						panic!("Closing nonexistent bracket!\n");
					}
				},

				Token::QT => {
					if !qtOpened {
						qtOpened = true;
					}


					else {
						if qtOpened && !qtClosed{
							if wasLt{ 
								qtOpened = false;
								qtClosed = true;
								c.push(wordBuf);
								wordBuf = String::new();
								wasLt = false;
							}

							else {
								panic!("Empty string not allowed!");
							}

						}

						else {
							panic!("Too many quotes");
						}
					}
				},

				Token::COM => {
					if wasDig {
						c.push(numBuf);
						numBuf = String::new();
						wasDig = false;
					}

					if wasLt {
						c.push(wordBuf);
						wordBuf = String::new();
						wasLt = false;
					}
				},
				Token::COL => {
					if wasLt {
						if isAttribute {
							c.push(wordBuf);
							wordBuf = String::new();
						}
					
						else {
							isAssignment = true;
							c.push(wordBuf);
							wordBuf = String::new();
						}	

						wasLt = false;
					}


					if bracketOpened == false && bracketClosed {
						isCommand = true;
					}


				},

				Token::LT(x) => {

					if wasLt == false {
						wasLt = true;
						wordBuf = String::from("");
					}

					wordBuf += x;
				},

				Token::DIG(x) => {
					if wasDig == false {
						wasDig = true;
						numBuf = String::from("");
					}

					numBuf += x;
				},

				

				_ => {
					if i.compare(Token::SPACE) == false {
						panic!("Unknown symbol found!");
					}
				}
			}
		}

		
		if isSection {
			c.push(wordBuf);
			typeBuf = EntryType::SECTION;
		}

		if isAttribute || isAssignment{
			c.push(numBuf);

			if isAssignment {
				typeBuf = EntryType::ASSIGN;
			}

			else {
				typeBuf = EntryType::ATTR;
			}
		}

		if isCommand {
			typeBuf = EntryType::COMMAND;
		}
		
		e = Entry{kind: typeBuf, content: c};

		return e;
	}

	
	pub fn addEntry(&mut self, e: Entry) {
		self.entryRegister.push_back(e);
	}


	pub fn printList(&self, l: &LinkedList<Entry>) {
		for i in l.iter() {
			i.printEntry();
		}
	}
}

