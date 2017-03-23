CC=g++
STYLECHECKER=python ../cpplint.py
OPT=-lgtest -lpthread
SRC := $(wildcard *.cpp)
OUT := $(subst .cpp,.o,$(SRC))


SRC_RUN := $(wildcard *Main.cpp)
RUN := $(subst .cpp,.exe,$(wildcard *Main.cpp))

SRC_TEST := $(wildcard *Test.cpp)
TEST := $(subst .cpp,.exe,$(wildcard *Test.cpp))

all: compile checkstyle test clean

compile: $(RUN)

$(RUN):	$(SRC_RUN)
	$(CC) -o $@ $?

checkstyle:
	$(STYLECHECKER) $(SRC)

test: $(TEST)

#include also all src to always recompule test when neccesary
$(TEST): $(SRC_TEST) $(SRC)
	$(CC) -o $@ $< $(OPT)
	./$(TEST)

clean:
	rm -f $(RUN) $(TEST) $(OUT)
