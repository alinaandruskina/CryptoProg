CXX = g++
CXXFLAGS = -std=c++17 -O2
LIBS = -lcryptopp

all: cipher_program

cipher_program: cipher_aes.cpp
	$(CXX) $(CXXFLAGS) -o cipher_program cipher_aes.cpp $(LIBS)

clean:
	rm -f cipher_program *.o
