CXX = clang++
CFLAGS = -O3 -Wall -Wextra -Wpedantic -std=c++11
SRC = src
OUT = brutus

all:
	rm -f -r build
	mkdir build
	mkdir build/release
	$(CXX) $(CFLAGS) $(SRC)/*.cpp -o build/release/$(OUT) 2> build/release/make.log
	cp charset.txt build/release/charset.txt
	cp dict.txt build/release/dict.txt
	cp *.md build/release/
	
	mkdir build/lib
	$(CXX) $(CFLAGS) -c $(filter-out $(SRC)/main.cpp, $(wildcard $(SRC)/*.cpp)) 2> build/lib/make.log
	ar rcs build/lib/libbrutus.a *.o
	rm *.o
	cp src/brutus.h build/lib/brutus.h
	cp charset.txt build/lib/charset.txt
	cp dict.txt build/lib/dict.txt
	cp *.md build/lib/

release:
	rm -f -r build
	mkdir build
	$(CXX) $(CFLAGS) $(SRC)/*.cpp -o build/$(OUT) 2> build/make.log
	cp charset.txt build/charset.txt
	cp dict.txt build/dict.txt
	cp *.md build/

static:
	rm -f -r build
	mkdir build
	$(CXX) $(CFLAGS) -c $(filter-out $(SRC)/main.cpp, $(wildcard $(SRC)/*.cpp)) 2> build/make.log
	ar rcs build/libbrutus.a *.o
	rm *.o
	cp src/brutus.h build/brutus.h
	cp charset.txt build/charset.txt
	cp dict.txt build/dict.txt
	cp *.md build/

.PHONY: analizer
analizer:
	rm -f -r analizer/build
	mkdir analizer/build
	$(CXX) $(CFLAGS) analizer/analizer.cpp -o analizer/build/analizer -Lbuild/lib -lbrutus 2> analizer/build/make.log
	cp analizer/analizer.py analizer/build/analizer.py
