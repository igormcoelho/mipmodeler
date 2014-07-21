program_SRCS := $(wildcard *.cpp)
program_H    := $(wildcard *.h)

all:
	astyle --style=allman $(program_H)	
	astyle --style=allman $(program_SRCS)
	rm -f *.orig
	g++ -O0 -g mip-main.cpp -o mipmodel
	g++ -Wall -Wempty-body -O0 -g emip-main.cpp Scanner++/Scanner.cpp -o emipmodel
