all: mark.h watermark.cpp
	g++ -Wall -g watermark.cpp -o watermark

rgb565: rgb565.cpp	
	g++ -Wall -g rgb565.cpp -o rgb565
