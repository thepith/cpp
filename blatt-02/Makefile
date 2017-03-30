CC=g++
STYLECHECKER=python ../cpplint.py
OPT=-lgtest -lpthread

.PRECIOUS: %.o

HEAD := $(wildcard *.h)
SRC := $(HEAD:.h=.cpp)
OBJ := $(HEAD:.h=.o)
RUN := $(subst .cpp,.exe,$(wildcard *Main.cpp))
TEST := $(subst .cpp,.exe,$(wildcard *Test.cpp))

all: compile checkstyle test clean

compile: $(RUN)

checkstyle:
	$(STYLECHECKER) *.cpp *.h

test: $(TEST)
	./$(TEST)

clean:
	rm -f *.exe *.o

%.o: %.cpp $(HEAD)
	$(CC) -c $<

%.exe: %.o $(OBJ)
	$(CC) -o $@ $^ $(OPT)
