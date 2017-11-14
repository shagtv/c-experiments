all: 		main

main: 		main.obj
		g++ bin/main.obj -o bin/main

main.obj: 	src/main.cpp
		g++ -c src/main.cpp -o bin/main.obj

clean:
		rm -rf bin/*

