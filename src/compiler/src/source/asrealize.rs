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
use super::fileHandler::FileHandler;
use super::token::Token;
use super::lexer::Lexer;
use super::entry::Entry;
use super::parser::Parser;
use super::binCoder::BinCoder;
use super::binFiler;
use std::collections::LinkedList;


pub fn openFile(p: String) -> Vec<String>{
	let mut con = String::new();
	let mut stringVec: Vec<String> = Vec::new();	

	let mut handler = FileHandler{path: p};
	let mut res = handler.handle();

	match res {
		Ok(x) => {
			con = x.clone();
			let mut splitted: Vec<&str> = con.split("\n").collect();
			let sz = splitted.len();

			for i in 0..sz {
				let mut c = String::from(splitted[i]);
				stringVec.push(c);
			}

			return stringVec;
		}

		Err(_y) => {
			panic!("Error when reading file!");
		}
	}
}


fn printTokenList(list: &LinkedList<Token>){
	for i in list.iter() {
		i.printToken();
	}
}

pub fn interpret(splitted: Vec<String>) -> LinkedList<Entry> {
	let mut lexer = Lexer{tokenList: LinkedList::new()};
	let mut parser = Parser{entryRegister: LinkedList::new()};
	let len = splitted.len();

		
	for i in 0..len {
		let mut s = splitted[i].clone();
		let mut tokenList = lexer.lex(s);
		//printTokenList(&tokenList);
		let mut e = parser.parse(tokenList);
		//e.printEntry();
		parser.addEntry(e);
		lexer.tokenList = LinkedList::new();
	}

	let reg = parser.entryRegister;
	return reg;
}

pub fn makeFile(binName: String, reg: &LinkedList<Entry>) {
	let mut bWri = BinCoder{data: Vec::new()};
	let d = bWri.writeData(reg);
//	binFiler::alternative(binName, &bWri.data);
	binFiler::writeBinaryFile(binName, &bWri.data);
}

pub fn modelFile(reg: &LinkedList<Entry>) {
	for i in reg.iter() {
		i.printEntry();
	}	
}

