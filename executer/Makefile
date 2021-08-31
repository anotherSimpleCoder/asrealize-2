SDL_FLAGS = -I /usr/local/include/SDL2 -D_REENTRANT
PNG_FLAGS = -I /usr/local/include/libpng16 -D_REENTRANT

CFLAGS = $(SDL_FLAGS) -I include

OPTIONS = -fsanitize=address

STANDARD = -std=c++17

LIBS = -lSDL2 -lpng

BIN_NAME = executer

compile:
	g++ $(CFLAGS) -c src/*.cpp $(OPTIONS) $(STANDARD)
	g++ $(CFLAGS) -c main.cpp -o main.o $(OPTIONS) $(STANDARD)
	g++ $(LIBS) -o $(BIN_NAME) *.o $(OPTIONS) $(STANDARD)
	rm *.o

noSan:
	g++ $(CFLAGS) -c src/*.cpp $(STANDARD) 
	g++ $(CFLAGS) -c main.cpp -o main.o $(STANDARD)
	g++ $(LIBS) -o $(BIN_NAME) *.o $(STANDARD)
	rm *.o

run:
	./$(BIN_NAME)
