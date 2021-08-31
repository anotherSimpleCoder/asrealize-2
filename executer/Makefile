CFLAGS = -I include

OPTIONS = -fsanitize=address

BIN_NAME = executer

compile:
	g++ $(CFLAGS) -c src/*.cpp $(OPTIONS)
	g++ $(CFLAGS) -c main.cpp -o main.o $(OPTIONS)
	g++ -o $(BIN_NAME) *.o $(OPTIONS)
	rm *.o

noSan:
	g++ $(CFLAGS) -c src/*.cpp 
	g++ $(CFLAGS) -c main.cpp -o main.o
	g++ -o $(BIN_NAME) *.o 
	rm *.o

run:
	./$(BIN_NAME)
