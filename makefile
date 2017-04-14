#Makefile to set up the enviroment

#CONFIGURATION

#MODIFY HERE!
#set libary path of gcc. Check with
# gcc -print-search-dirs
#which directories are used
#gcc under cygwin uses usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/
GCCLIB=/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/

##variables
lecture_dir:=lecture_files/
movie_dir:=$(lecture_dir)videos/
movies:=$(shell for n in `seq -w 1 12`; do echo "vorlesung-$$n.mp4" ;done)
movie_files=$(addprefix $(movie_dir),$(movies))

##ALL
all: depend lecture

##DEPENDECIES
#build the files the exercises need
depend:	gtest cpplint

###GTEST
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

##CPPLINT
cpplint: cpplint.py

lecture: videos svndata

videos: $(movie_files)

%.mp4:  $(movie_dir)
	wget -nc --no-use-server-timestamps http://ad-teaching.informatik.uni-freiburg.de/ProgrammierenCplusplusSS2016/$(notdir $@) -O $@

%/:
	mkdir -p $@

svndata: $(lecture_dir)svn-public

$(lecture_dir)public: $(lecture_dir)
	cd $(lecture_dir); git svn clone https://daphne.informatik.uni-freiburg.de/ss2016/ProgrammierenCplusplus/svn-public/public; rm -rf public/.git


code: $(code_dir)
	wget -P $< -r --no-parent -A 'vorlesung*/*/*' https://daphne.informatik.uni-freiburg.de/ss2016/ProgrammierenCplusplus/svn-public/public/code/

cpplint.py: styleguide/cpplint/cpplint.py
	ln -s $< $@

styleguide/cpplint/cpplint.py:
	git submodule update --init styleguide

clean:
	rm -rf styleguide googletest
	mkdir styleguide
	mkdir googletest
