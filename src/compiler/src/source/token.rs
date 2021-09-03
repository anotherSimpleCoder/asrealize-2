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
