all:
	g++ -Iinclude/  ./src/cpu.cpp ./src/ram.cpp ./src/testMain.cpp -o posNes \
		-std=c++11

clean:
	rm posNes
