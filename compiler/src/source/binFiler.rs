use std::fs::File;
use std::io::Write;
use std::io::prelude::*;
use std::collections::LinkedList;
use byteorder::{LittleEndian, WriteBytesExt};

pub fn writeBinaryFile(path: String, data: &Vec<u16>) -> std::io::Result<()> {
	let mut file = File::create(path.to_string())?;
	let s = data.len();
	let slices = &data[0..s];

	println!("{:#04x?}", slices);
/*
	for i in slices.iter() {
		println!("{:b}", i);	
	}
*/
	let mut result: Vec<u8> = Vec::new();

	for &i in slices {
		//println!("{}", i);
		let x = result.write_u16::<LittleEndian>(i);
	}

	let resultSize = result.len();
	
/*
	for i in result.iter() {
		println!("{}", i);
	}
*/
	let finalData = &result[0..resultSize];
/*
	println!();
	println!();

	for i in finalData.iter() {
		println!("{:b}", i);
	}
*/	
	//println!("{:b?}", &result[0..resultSize]);
/*
	for i in result.iter() {
		let h = &i[0];
		println!("{:?}", &h);
		file.write(h)?;
	}
*/
	file.write_all(&result[0..resultSize])?;
	Ok(())
}

use std::{mem, slice};

pub fn alternative(path: String, data: &Vec<u16>) {
	println!("{:#4x?}", data);

	let s = data.len();
	let slices = &data[0..s];

	let slice_u8: &[u8] = unsafe {
		slice::from_raw_parts(
			slices.as_ptr() as *const u8,
			slices.len() * mem::size_of::<u16>(),
		)
	};

	println!("{:#4x?}", slice_u8);
}

