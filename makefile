all: driver.x mydriver.x

driver.x: driver.o tlist.h tnode.h
	g++ -o driver.x driver.o

mydriver.x: mydriver.o tlist.h tnode.h
	g++ -o mydriver.x mydriver.o

driver.o: driver.cpp tlist.h tnode.h
	g++ -c -std=c++11 driver.cpp

mydriver.o: mydriver.cpp tlist.h tnode.h
	g++ -c -std=c++11 mydriver.cpp

clean:
	rm -f driver.x mydriver.x *.o
