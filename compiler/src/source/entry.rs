use super::entryType::EntryType;
use std::collections::LinkedList;

pub struct Entry{
	pub kind: EntryType,
	pub content: Vec<String>
}

impl Entry{
	pub fn printEntry(&self){
		let strType = self.kind.to_string();
		let mut con = String::from("");
		
		for i in self.content.iter() {
			con = con + ", " + i;
		}

		println!("{}  {}", strType, con);
	}
}

/*
fn main(){
	let mut list: LinkedList<String> = LinkedList::new();
	list.push_back(String::from("x"));	
	list.push_back(String::from("3"));

	let mut e = Entry{kind: entryType::entryType::ASSIGN, content: list};

	e.printEntry();
}
*/
