CXX = clang++
CFLAGS = -O3 -Wall -Wextra -Wpedantic -std=c++11
SRC = src
OUT = build/brutus

all:
	$(CXX) $(CFLAGS) $(SRC)/*.cpp -o $(OUT) 2> build/make.log
	cp charset.txt build/charset.txt
	cp dict.txt build/dict.txt

clean:
	rm -f $(OUT)
