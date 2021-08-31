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

