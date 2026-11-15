CXX = g++
CXXFLAGS = -std=c++17 -O2
LIBS = -lcryptopp

all: hash_program

hash_program: hash_sha512.cpp
	$(CXX) $(CXXFLAGS) -o hash_program hash_sha512.cpp $(LIBS)

clean:
	rm -f hash_program *.o
