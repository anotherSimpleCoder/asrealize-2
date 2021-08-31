use std::fs::File;
use std::io::BufReader;
use std::io::prelude::*;

pub struct FileHandler {
	pub path: String,
	//pub content: String
}

impl FileHandler {
	pub fn handle(&mut self) -> std::io::Result<String> {
		let mut content = String::new();
		let mut file = File::open(&(self.path))?;
		let mut bufReader = BufReader::new(file);
		
		bufReader.read_to_string(&mut content)?;
		//println!("{}" , self.content);
		Ok(content)
	}
}
