all:
	g++ main.cpp src/* \
	-lcppunit  -I../include -std=c++11 ../src/cpu.cpp\
	 ../src/memory_unit.cpp ../src/ram_unit.cpp  -o test
	./test
	rm test