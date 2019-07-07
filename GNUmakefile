compiler = g++
compiling-flags = -std=c++17
linking-flags = -lSDL2 -lboost_filesystem -lpng -ljpeg

headers = src/error.hpp src/pixmap.hpp src/macros.hpp
sources = src/error.cpp src/pixmap.cpp src/test.cpp
build/test : $(headers) $(sources)
	$(compiler) -o build/test $(compiling-flags) $(linking-flags) $(sources)
