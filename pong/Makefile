all: 		main

main: 		main.obj
		g++ -std=c++11 bin/main.obj -o bin/main -lncurses

main.obj: 	src/main.cpp
		g++ -std=c++11 -c src/main.cpp -o bin/main.obj

clean:
		rm -rf bin/*

