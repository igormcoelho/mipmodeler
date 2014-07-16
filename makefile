all:
	g++ -O0 -g mip-main.cpp -o mipmodel
	g++ -Wall -Wempty-body -O0 -g emip-main.cpp Scanner++/Scanner.cpp -o emipmodel
