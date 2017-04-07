all: compile test checkstyle

compile: GravitonMain

test: GravitonTest
	./GravitonTest

checkstyle:
	python ../cpplint.py *.cpp *.h

clean:
	rm -f *.o
	rm -f GravitonMain
	rm -f GravitonTest

GravitonMain: Graviton.o GravitonMain.o
	g++ -o GravitonMain GravitonMain.o Graviton.o -lncurses

GravitonTest: Graviton.o GravitonTest.o
	g++ -o GravitonTest GravitonTest.o Graviton.o -lgtest -lpthread -lncurses

Graviton.o: Graviton.cpp Graviton.h
	g++ -c Graviton.cpp

GravitonMain.o: GravitonMain.cpp Graviton.h
	g++ -c GravitonMain.cpp

GravitonTest.o: GravitonTest.cpp Graviton.h
	g++ -c GravitonTest.cpp
