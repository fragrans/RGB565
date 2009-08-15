.PHONY : all rgb565
all: mark.h watermark.cpp rgb565
	g++ -Wall -g watermark.cpp -o watermark

rgb565: rgb565.cpp	
	g++ -Wall -g rgb565.cpp -o rgb565
