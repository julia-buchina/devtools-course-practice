all:
	mkdir -p ./build
	$(CXX) -o ./build/calc ./src/simplecalc.cc ./samples/calc.cpp -I./include

test: all
	./build/calc