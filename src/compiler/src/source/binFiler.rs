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
use std::fs::File;
use std::io::Write;
use std::io::prelude::*;
use std::collections::LinkedList;
use byteorder::{LittleEndian, WriteBytesExt};

pub fn writeBinaryFile(path: String, data: &Vec<u16>) -> std::io::Result<()> {
	let mut file = File::create(path.to_string())?;
	let s = data.len();
	let slices = &data[0..s];

//	println!("{:#04x?}", slices);
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

