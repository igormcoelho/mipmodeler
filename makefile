program_SRCS := $(wildcard *.cpp)
program_H    := $(wildcard *.h)

all:
#	astyle --style=allman $(program_H) > /dev/null	
#	astyle --style=allman $(program_SRCS) > /dev/null
#	rm -f *.orig
	g++ -O0 -g mip-main.cpp -o mipmodel
	g++ -Wall -Wempty-body -O0 -g emip-main.cpp EMIP/Scanner++/Scanner.cpp -o emipmodel
	g++ mimic/mimic.cpp -g -o appMimic
