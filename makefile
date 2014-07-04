all:
	g++ -O0 -g mip-main.cpp -o mipmodel
	g++ -O0 -g -std=c++11 emip-main.cpp -o emipmodel
