mod source;

use source::asrealize;
use source::binCoder::BinCoder;
use source::binFiler;
use std::collections::LinkedList;
use std::env;

fn main(){
	let args: Vec<String> = env::args().collect();

	if args.len() != 3 {
		panic!("Insufficient arguments!");
	}

	else{
		let src = &args[1];
		let out	= &args[2];

		let fCon = asrealize::openFile(src.to_string());
		let eCon = asrealize::interpret(fCon);
		asrealize::makeFile(out.to_string(), &eCon);
	}
}
