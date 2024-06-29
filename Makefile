CXX = g++
CFLAGS = -O3 -Wall -Wextra -Wpedantic -std=c++11
SRC = src
OUT = main

all:
	$(CXX) $(CFLAGS) $(SRC)/*.cpp -o $(OUT)

clean:
	rm -f $(OUT)