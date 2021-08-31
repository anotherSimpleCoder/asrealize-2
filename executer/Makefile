CFLAGS = -I include

OPTIONS = -fsanitize=address

STANDARD = -std=c++17

BIN_NAME = executer

compile:
	g++ $(CFLAGS) -c src/*.cpp $(OPTIONS) $(STANDARD)
	g++ $(CFLAGS) -c main.cpp -o main.o $(OPTIONS) $(STANDARD)
	g++ -o $(BIN_NAME) *.o $(OPTIONS) $(STANDARD)
	rm *.o

noSan:
	g++ $(CFLAGS) -c src/*.cpp $(STANDARD) 
	g++ $(CFLAGS) -c main.cpp -o main.o $(STANDARD)
	g++ -o $(BIN_NAME) *.o $(STANDARD)
	rm *.o

run:
	./$(BIN_NAME)
