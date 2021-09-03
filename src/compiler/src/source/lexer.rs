use super::token::Token;
use std::collections::LinkedList;
use std::char;


pub struct Lexer{
	pub tokenList: LinkedList<Token>
}

impl Lexer {
	
	fn charToToken(&self, c:char)-> Token{
		match c{
			//non parametric
			'#' => return Token::HASH, 
			'-' => return Token::DASH,
			'(' => return Token::OB,
			')' => return Token::CB,
			',' => return Token::COM,
			':' => return Token::COL,
			'\"'  => return Token::QT,
			'\n' => return Token::NWLINE,
			' ' => return Token::SPACE,

			_ => if c.is_alphabetic(){
				return Token::LT(c.to_string());	
			}

			else if c.is_numeric(){
				return Token::DIG(c.to_string());
			}

			else{
				return Token::NUL;				
			}
		}
	}

	
	
	pub fn lex(&mut self, line:String) -> &LinkedList<Token> {
		let mut t: Token;
		
		for i in 0..line.len() { 
			let c = line.chars().nth(i).unwrap();
			t = self.charToToken(c);
			self.tokenList.push_back(t);
			//t.printToken();
		}
		//println!("{}", line);
		return &(self.tokenList);
	}

/*
	pub fn printList(&self, list: &LinkedList<Token>){
		for i in list.iter() {
			i.printToken();	
		}
	}
*/
}


/*
fn main() {

	let mut l = Lexer{tokenList: LinkedList::new()};
	l.lex(String::from("x:3"));	
	l.printList();
}
*/



