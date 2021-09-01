pub enum EntryType{
	SECTION,	//#meta
	ATTR,		//-height
	COMMAND,	//(3,3) : ...
	ASSIGN,		//x:3
	NUL		
}

impl EntryType{
	pub fn to_string(&self) -> String {
		match self {
			EntryType::SECTION => return String::from("SECTION"),
			EntryType::ATTR => return String::from("ATTR"),
			EntryType::COMMAND => return String::from("COMMAND"),
			EntryType::ASSIGN => return String::from("ASSIGN"),
			EntryType::NUL => return String::from("NUL")
		}
	}
}
