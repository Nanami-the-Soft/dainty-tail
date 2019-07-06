compiler = g++
compiling-flags = -std=c++17
linking-flags = -lSDL2

headers = src/error.hpp
sources = src/error.cpp src/test.cpp
build/test : $(headers) $(sources)
	$(compiler) -o build/test $(compiling-flags) $(linking-flags) $(sources)
