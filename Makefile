CXX = g++
CFLAGS = -O3 -Wall -Wextra -Wpedantic -std=c++11
SRC = src
OUT = brutus

all:
	$(CXX) $(CFLAGS) $(SRC)/*.cpp -o $(OUT)

clean:
	rm -f $(OUT)