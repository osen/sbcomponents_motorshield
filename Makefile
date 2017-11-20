all:
	g++ -std=c++11 -g -o motorhat *.cpp -lwiringPi -lpthread -lcrypt -lrt

clean:
	rm motorhat
