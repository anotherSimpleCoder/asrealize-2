#asrealize-2


Documentation
-------------

asrealize-2 is the second revision of formerly named interpreter ASRealize1. It's built using the newest asr library and has following changes:

 - instead of interpreting the asr file is being compiled
 - it solely supports a new standard of asrScript (asrScript standard alpha won't be supported anymore)
 - since asr-v2 has png support this revision of asrealize also has png support and it's possible to compile your asr file into a png file as well


Notice
------

Some of you might have realized that asr and also asrealize don't have any Windows binaries, That's due to compilation issues I am having and I am currently
just able to compile software for macOS and GNU/Linux.


Getting started
---------------

As said in asrealize-2 it is not required to have the SDL2 framework installed again if you are into granular access for multimedia projects definetly go and check it out :)

If you want to run your asrscript directly just enter:
```bash
./asrealize2 <path to your .asr file>
```

However since there is now the option to compile your image to a PNG file. And in order to do that just enter the follwing:
```bash
./asrealize <path to your .asr file> -png
```

How does asrealize2 work?
-------------------------

There are still some things that are similar to asrealize-1 functionality-wise. However there are some new steps included, which also make asrealize2 now a compiler instead of an interpreter.
First the .asr file gets passed to the asrealize2-compiler (binary also included), which compiles the asr file into an .asb file (another simple binary). An asb file is a binary file containing instructions for the asrealize2-executer. The executer loads the binary file into it's data buffer, checks also again for any errors (if there were any made during compilation) and then runs it by either creating a .png file or just displaying it. The asrealize2 binary just combines these two components and thats it. If you really want to do those steps seperate just do the following:

 1) Compile the .asr file to an .asb file:
```bash
./asrealize2-compiler <path to your asr file>
```

 2) Run the .asb file with the executer:
```bash
./asrealize2-executer <path to your asb file> <"-png" if you want a png>
```

There will also be a more detailed explaination how stuff works under the hood in a seperate document ;)


Building
--------



There are binaries included for both Linux and MacOS (sry Windows users but I cannot figure out the compilation for you guys :( ). HOWEVER if your operating system isn't able to run asrealize2 (or you are a Windows user) then builing is the next best option.

To build asrealize2 you need the following libraries:
	* SDL2
	* libpng
	* (and if not included in libpng) zlib

Also you need to have following software installed:
	* clang
	* make
	* cargo

You can get these libraries the following way:

Debian/Ubuntu (or other Debian derivates):

```bash
sudo apt-get install libsdl2-dev libpng-dev
```

Arch Linux:
```bash
sudo pacman -S sdl2 libpng 
```

Fedora/CentOS:
```bash
sudo dnf install sdl2 libpng
```

macOS:
```bash
brew install sdl2 libpng
```

After you're done with that change to the following directory:
```bash
cd <directory where asrealize is located>/asrealize-2/src
```

Now we have to compile the compiler (hehe):

In order to do that just change to the compiler directory:
```bash
cd compiler
```

Then just run following command:
```bash
cargo build
```

And there you have your compiler!
Tip: It's advised to create a build folder where you move your built executables to!



