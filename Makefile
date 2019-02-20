MUDUO_DIRECTORY = /home/bing/CPP/Linux多线程-陈硕/build/release-install
#MUDUO_DIRECTORY ?= $(HOME)/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
SRC = ./src

CXXFLAGS = -std=c++11 -g -O0 -Wall -Wextra -Werror \
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -I$(MUDUO_INCLUDE)

LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lmuduo_http -lpthread -lrt

all: main
clean:
	rm -f main core

main: $(SRC)/main.o $(SRC)/response.o 
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean