all:
	mkdir -p ./build
	$(CXX) -o ./build/calc ./library/src/simplecalc.cc ./sample/calc.cpp ./library/src/calc_application.cc -I./

test: all
	./build/calc
