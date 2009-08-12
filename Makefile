all: rgb565.cpp mark.cpp
	g++ -g -Wall -o  rgb565 rgb565.cpp
	g++ -g -Wall -o mark mark.cpp
