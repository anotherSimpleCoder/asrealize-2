SDL_FLAGS = -I /usr/local/include/SDL2 -D_REENTRANT
PNG_FLAGS = -I /usr/local/include/libpng16 -D_REENTRANT

CFLAGS = $(SDL_FLAGS) -I include

OPTIONS = -fsanitize=address

STANDARD = -std=c++17

LIBS = -lSDL2 -lpng

BIN_NAME = executer

compile:
	clang++ $(CFLAGS) -c src/*.cpp $(OPTIONS) $(STANDARD)
	clang++ $(CFLAGS) -c main.cpp -o main.o $(OPTIONS) $(STANDARD)
	clang++ $(LIBS) -o $(BIN_NAME) *.o $(OPTIONS) $(STANDARD)
	rm *.o

noSan:
	clang++ $(CFLAGS) -c src/*.cpp $(STANDARD) 
	clang++ $(CFLAGS) -c main.cpp -o main.o $(STANDARD)
	clang++ $(LIBS) -o $(BIN_NAME) *.o $(STANDARD)
	rm *.o

log:
	clang++ $(CFLAGS) -c src/*.cpp $(OPTIONS) $(STANDARD)
	clang++ $(CFLAGS) -c log1.cpp -o log1.o $(OPTIONS) $(STANDARD)
	clang++ $(LIBS) -o log1 *.o $(OPTIONS) $(STANDARD)	
	rm log1.o
	clang++ $(CFLAGS) -c log2.cpp -o log2.o $(OPTIONS) $(STANDARD)
	clang++ $(LIBS) -o log2 *.o $(OPTIONS) $(STANDARD)
	rm log2.o	
	clang++ $(CFLAGS) -c log3.cpp -o log3.o $(OPTIONS) $(STANDARD)
	clang++ $(LIBS) -o log3 *.o $(OPTIONS) $(STANDARD)
	rm *.o
	./log1 >> log1.txt
	./log2 >> log2.txt
	./log3 >> log3.txt
	rm log1 log2 log3
	clear

removeLog:
	rm *.txt
	clear

clean:
	rm *.o
	clear

run:
	./$(BIN_NAME)
