all:
	g++ -O0 -g mip-main.cpp -o mipmodel
	g++ -Wall -O0 -g emip-main.cpp -o emipmodel
