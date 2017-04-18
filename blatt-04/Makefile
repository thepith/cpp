CC=g++
STYLECHECKER=python ../cpplint.py --root=.
OPTTEST=-lgtest -lpthread -lgtest_main
OPT=-lncurses

.PRECIOUS: %.o

HEAD := $(wildcard *.h)
SRC := $(HEAD:.h=.cpp)
OBJ := $(HEAD:.h=.o)
RUN := $(subst .cpp,.exe,$(wildcard *Main.cpp))
TEST := $(subst .cpp,.exe,$(wildcard *Test.cpp))

all: compile checkstyle test

run: compile
	./$(RUN)
compile: $(RUN)

checkstyle:
	$(STYLECHECKER) *.cpp *.h

test: $(TEST)
	./$(TEST)

clean:
	rm -f *.exe *.o

%.o: %.cpp $(HEAD)
	$(CC) -o $@ -c $< $(OPT)

%Main.exe: %Main.o $(OBJ)
	$(CC) -o $@ $^ $(OPT)

%Test.exe: %Test.o $(OBJ)
	$(CC) -o $@ $^ $(OPTTEST) $(OPT)
