#Makefile to set up the enviroment

#set libary path of gcc. Check with 
# gcc -print-search-dirs
#which directories are used
#gcc under cygwin uses usr/lib
GCCLIB=/usr/lib/

#build the files the exercises need
depend:	gtest cpplint

gtest: $(GCCLIB)/gtest.h $(GCCLIB)/libgtest_main.a $(GCCLIB)/libgtest.a

$(GCCLIB)/gtest.h: googletest/googletest/include/gtest/gtest.h
	cp -a $< $@

$(GCCLIB)/%.a: googletest/googletest/%.a
	cp -a $< $@

googletest/googletest/libgtest.a: googletest/googletest/CMakeLists.txt
	cd googletest/googletest/ ; cmake . ; make

googletest/googletest/libgtest_main.a: googletest/googletest/libgtest.a

googletest/googletest/include/gtest/gtest.h: googletest/googletest/libgtest.a

googletest/googletest/CMakeLists.txt:
	git submodule update --init googletest

cpplint: cpplint.sty

cpplint.py: styleguide/cpplint/cpplint.py
	ln -s $< $@

styleguide/cpplint/cpplint.py:
	git submodule update --init styleguide
