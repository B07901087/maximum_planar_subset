
CC = g++
OPTFLAGS = -O3 -std=c++11 -Wall
BIN=mps
$(BIN) 	: src/maxPlanarSubset.cpp
	@$(CC) $< -o $@ $(OPTFLAGS)




clean:
	@rm -f $(BIN)