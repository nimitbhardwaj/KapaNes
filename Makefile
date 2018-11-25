all:
	g++ -Iinclude/  ./src/cpu.cpp ./src/memory_unit.cpp ./src/testMain.cpp \
	./src/ram_unit.cpp -o kapaNes -std=c++11

clean:
	rm kapaNes

test:
	cd tests && make
